# cpp/exercises/practice/cmake/cpptest-postbuild.cmake
# ====================================================
# Protect against double-include
if(DEFINED _CPPT_HOOK_LOADED)
    return()
endif()
set(_CPPT_HOOK_LOADED TRUE)

# ------------- user customisation via env vars ------------------------------
set(CPPTEST_CONFIG $ENV{CPPTEST_CONFIG})
if(NOT CPPTEST_CONFIG)
    set(CPPTEST_CONFIG "builtin://Recommended Rules")
endif()

set(BUILD_ID $ENV{BUILD_ID})

# ------------- locate Parasoft ---------------------------------------------
set(CPPTEST_HOME $ENV{CPPTEST_HOME})
if(NOT EXISTS "${CPPTEST_HOME}/cpptestcli")
    message(FATAL_ERROR "cpptestcli not found; export CPPTEST_HOME")
endif()
set(_CPPTCLI "${CPPTEST_HOME}/cpptestcli")

# ------------- helper that hooks ONE executable ----------------------------
function(_cpptest_attach TARGET_NAME)
    if(_cpptest_attached_${TARGET_NAME})
        return()                       # idempotent
    endif()
    set(_cpptest_attached_${TARGET_NAME} TRUE PARENT_SCOPE)

    # base dir for reports
    set(_REPORT_DIR "${CMAKE_BINARY_DIR}/cpptest_reports")

    # assemble cli argument list
    set(_ARGS
        "-input"      "${CMAKE_BINARY_DIR}/compile_commands.json"
        "-module"     .
        "-config"     "${CPPTEST_CONFIG}"
        "-report"     "${_REPORT_DIR}"
        "-workspace"  "${CMAKE_BINARY_DIR}/cpptest_ws"
        "-exclude" "*_test.cpp"  "-exclude" "*/test/*"
        "-property" "session.tag=${TARGET_NAME}"
    )
    if(BUILD_ID)
        list(APPEND _ARGS -property "build.id=${BUILD_ID}")
    endif()

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_REPORT_DIR}"
        COMMAND "${_CPPTCLI}" -compiler gcc_11-64 -property dtp.project=ML ${_ARGS} > "${_REPORT_DIR}/cpptestcli.log" 2>&1
        VERBATIM)
endfunction()

# ------------- attach to every non-test executable in this dir -------------
get_property(_tgt_list DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
foreach(t IN LISTS _tgt_list)
    get_target_property(_kind ${t} TYPE)
    if(_kind STREQUAL "EXECUTABLE" AND NOT t MATCHES "^test_")
        _cpptest_attach(${t})
    endif()
endforeach()
