#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    violets,
    radishes,
    clover,
    grass
};

class garden {
public:
    // Constructor using the default, alphabetically-sorted pupil list.
    explicit garden(std::string_view diagram);

    // Constructor that accepts a custom, pre-sorted pupil list.
    garden(std::string_view           diagram,
           const std::vector<std::string>& students);

    // Return the four plants assigned to the named pupil.
    [[nodiscard]] std::array<Plants, 4U> plants(std::string_view pupil) const;

private:
    static constexpr std::array<const char*, 12U> default_pupils_{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };

    [[nodiscard]] static Plants char_to_plant(char code);

    std::vector<std::string> pupils_{};
    std::array<std::string, 2U> rows_{};
};

}  // namespace kindergarten_garden
