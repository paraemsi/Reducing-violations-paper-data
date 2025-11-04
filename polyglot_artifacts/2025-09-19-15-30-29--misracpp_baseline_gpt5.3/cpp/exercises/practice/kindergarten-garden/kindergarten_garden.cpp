#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <cstddef>

namespace kindergarten_garden {

namespace {

// Default list of students in alphabetical order.
const std::vector<std::string>& default_students() {
    static const std::vector<std::string> students = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    return students;
}

Plants char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument("Unknown plant code");
    }
}

std::pair<std::string, std::string> split_rows(const std::string& diagram) {
    auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        // If there's only one line, treat second line as empty.
        return {diagram, std::string{}};
    }
    // Only consider the first two rows; ignore any extra content.
    std::string row1 = diagram.substr(0, pos);
    std::string rest = diagram.substr(pos + 1);
    auto pos2 = rest.find('\n');
    std::string row2 = pos2 == std::string::npos ? rest : rest.substr(0, pos2);
    return {row1, row2};
}

}  // namespace

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    auto [row1, row2] = split_rows(diagram);

    // Copy and sort student names alphabetically, as per assignment rules.
    std::vector<std::string> sorted = students;
    std::sort(sorted.begin(), sorted.end());

    for (std::size_t i = 0; i < sorted.size(); ++i) {
        const std::size_t idx = 2 * i;

        // Ensure indices are within bounds; if not, stop assigning further.
        if (row1.size() < idx + 2 || row2.size() < idx + 2) {
            break;
        }

        std::array<Plants, 4> ps{
            char_to_plant(row1[idx]),
            char_to_plant(row1[idx + 1]),
            char_to_plant(row2[idx]),
            char_to_plant(row2[idx + 1])
        };

        assignments_.emplace(sorted[i], std::move(ps));
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        return {};
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g{diagram};
    return g.plants(student);
}

}  // namespace kindergarten_garden
