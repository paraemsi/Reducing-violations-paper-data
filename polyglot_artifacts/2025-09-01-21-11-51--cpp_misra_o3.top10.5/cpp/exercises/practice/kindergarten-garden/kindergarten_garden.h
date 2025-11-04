#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

using plant = Plants;

class garden {
public:
    garden(std::string_view diagram,
           std::vector<std::string> students = { "Alice", "Bob", "Charlie", "David",
                                                 "Eve", "Fred", "Ginny", "Harriet",
                                                 "Ileana", "Joseph", "Kincaid", "Larry" });

    [[nodiscard]] std::vector<plant> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<plant>> student_plants_;

    static plant char_to_plant(char c);
};

[[nodiscard]] std::array<Plants, 4U> plants(std::string_view diagram,
                                            std::string_view student,
                                            std::vector<std::string> students = { "Alice", "Bob", "Charlie", "David",
                                                                                  "Eve", "Fred", "Ginny", "Harriet",
                                                                                  "Ileana", "Joseph", "Kincaid", "Larry" });

}  // namespace kindergarten_garden
