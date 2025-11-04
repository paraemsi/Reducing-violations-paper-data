#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    // Construct a garden from a diagram and an optional, possibly unsorted,
    // list of student names.  If no list is supplied the canonical roster is
    // used.
    garden(std::string_view diagram,
           std::vector<std::string> students = {
               "Alice",  "Bob",   "Charlie", "David",
               "Eve",    "Fred",  "Ginny",   "Harriet",
               "Ileana", "Joseph","Kincaid", "Larry"});

    // Return the 4 plants belonging to the requested student in reading order:
    // two from the first row followed by two from the second.
    std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;
};

std::array<Plants, 4> plants(std::string_view diagram,
                             const std::string& student,
                             std::vector<std::string> students = {
                                 "Alice",  "Bob",   "Charlie", "David",
                                 "Eve",    "Fred",  "Ginny",   "Harriet",
                                 "Ileana", "Joseph","Kincaid", "Larry"});
}  // namespace kindergarten_garden
