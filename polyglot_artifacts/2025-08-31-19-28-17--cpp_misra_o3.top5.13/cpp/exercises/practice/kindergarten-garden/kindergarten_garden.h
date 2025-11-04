#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

/* Enumeration listing the possible plants. */
enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

/* Class that represents the whole kindergarten garden. */
class garden final {
public:
    explicit garden(std::string_view diagram);

    /* Return the four plants that belong to the given student. */
    [[nodiscard]] std::vector<Plants> plants(std::string_view student) const;

private:
    static Plants char_to_plant(char c);

    std::unordered_map<std::string, std::array<Plants, 4U>> m_student_plants;
};

std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student);

}  // namespace kindergarten_garden
