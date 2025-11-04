#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <array>

#if (__cplusplus >= 201703L)
#define KG_NODISCARD [[nodiscard]]
#else
#define KG_NODISCARD
#endif

namespace kindergarten_garden {

// Default list of students in alphabetical order
KG_NODISCARD std::vector<std::string_view> default_students();

enum class Plants : std::uint8_t
{
    grass,
    clover,
    radishes,
    violets
};

class garden final
{
public:
    explicit garden(std::string_view diagram,
                    std::vector<std::string_view> students = default_students());

    KG_NODISCARD std::vector<Plants> plants(std::string_view student) const;

private:
    static Plants char_to_plant(char diagram_char);

    std::unordered_map<std::string, std::vector<Plants>> m_assignments;
};

KG_NODISCARD std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student);

} // namespace kindergarten_garden
