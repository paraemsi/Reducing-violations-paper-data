#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace {

const std::array<const char*, 12> children{
    "Alice", "Bob",   "Charlie", "David", "Eve",    "Fred",
    "Ginny", "Harriet", "Ileana",  "Joseph", "Kincaid", "Larry"};

Plants to_Plants(char plant_code) {
    switch (plant_code) {
        case 'V': return Plants::violets;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'G': return Plants::grass;
        default: throw std::invalid_argument("Invalid plant code.");
    }
}

}  // namespace

std::vector<Plants> plants(const std::string& diagram, const std::string& name) {
    const size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Malformed diagram: missing newline.");
    }
    const std::string row1 = diagram.substr(0, newline_pos);
    const std::string row2 = diagram.substr(newline_pos + 1);

    if (row1.length() != row2.length()) {
        throw std::invalid_argument("Diagram has rows of unequal length.");
    }
    if (row1.length() % 2 != 0) {
        throw std::invalid_argument("Diagram has rows of odd length.");
    }

    const auto it = std::find(children.begin(), children.end(), name);
    const size_t child_index = std::distance(children.begin(), it);
    const size_t start_pos = child_index * 2;

    return {
        to_Plants(row1.at(start_pos)),
        to_Plants(row1.at(start_pos + 1)),
        to_Plants(row2.at(start_pos)),
        to_Plants(row2.at(start_pos + 1))
    };
}

}  // namespace kindergarten_garden
