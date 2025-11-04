#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

/* Alias required by the tests – gives access to the same enumerators
 * through the kindergarten_garden::Plants name. */
using Plants = plant;

class garden {
public:
    explicit garden(std::string_view diagram);
    garden(std::string_view diagram, std::vector<std::string> students);

    [[nodiscard]] std::vector<plant> plants(const std::string& student_name) const;

private:
    std::map<std::string, std::vector<plant>> student_plants_{};

    static plant char_to_plant(char code);
    static std::vector<std::string> default_students();
};

[[nodiscard]] std::array<plant, 4U> plants(std::string_view diagram,
                                           std::string_view student_name);

}  // namespace kindergarten_garden
