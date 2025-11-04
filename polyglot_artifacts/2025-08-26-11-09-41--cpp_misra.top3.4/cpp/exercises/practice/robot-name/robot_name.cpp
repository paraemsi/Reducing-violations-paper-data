#include "robot_name.h"
#include <random>
#include <mutex>
#include <array>
#include <algorithm>

namespace robot_name {

::std::unordered_set<::std::string> robot::s_used_names;

namespace {
    // Thread-safe random engine
    ::std::mt19937& get_rng() {
        static ::std::random_device rd;
        static ::std::mt19937 rng(rd());
        return rng;
    }

    // Mutex for protecting s_used_names
    ::std::mutex& get_mutex() {
        static ::std::mutex mtx;
        return mtx;
    }
}

robot::robot()
    : m_name()
{
    // Robot starts with no name
}

robot::~robot()
{
    if (!m_name.empty()) {
        ::std::lock_guard<::std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
    }
}

::std::string robot::name(void)
{
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    if (!m_name.empty()) {
        ::std::lock_guard<::std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
        m_name.clear();
    }
}

::std::string robot::generate_unique_name(void)
{
    ::std::string candidate;
    ::std::lock_guard<::std::mutex> lock(get_mutex());
    do {
        candidate = generate_name();
    } while (s_used_names.find(candidate) != s_used_names.end());
    s_used_names.insert(candidate);
    return candidate;
}

::std::string robot::generate_name(void)
{
    // Format: two uppercase letters + three digits
    ::std::array<char, 5U> arr{};
    arr[0] = static_cast<char>('A' + static_cast<::std::int32_t>(random_uint32(0U, 25U)));
    arr[1] = static_cast<char>('A' + static_cast<::std::int32_t>(random_uint32(0U, 25U)));
    arr[2] = static_cast<char>('0' + static_cast<::std::int32_t>(random_uint32(0U, 9U)));
    arr[3] = static_cast<char>('0' + static_cast<::std::int32_t>(random_uint32(0U, 9U)));
    arr[4] = static_cast<char>('0' + static_cast<::std::int32_t>(random_uint32(0U, 9U)));
    return ::std::string(arr.data(), arr.size());
}

::std::uint32_t robot::random_uint32(::std::uint32_t min, ::std::uint32_t max)
{
    // Inclusive range [min, max]
    ::std::uniform_int_distribution<::std::uint32_t> dist(min, max);
    return dist(get_rng());
}

}  // namespace robot_name
