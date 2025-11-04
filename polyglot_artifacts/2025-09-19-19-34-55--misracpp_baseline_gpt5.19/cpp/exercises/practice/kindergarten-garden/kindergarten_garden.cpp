#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

namespace {

Plants from_char(char c) {
    switch (c) {
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<std::string> default_students() {
    return {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}

}  // namespace

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split diagram into two rows
    const auto pos = diagram.find('\n');
    const std::string row1 = diagram.substr(0, pos);
    const std::string row2 = (pos == std::string::npos) ? std::string() : diagram.substr(pos + 1);

    // Sort students alphabetically
    std::vector<std::string> sorted = students;
    std::sort(sorted.begin(), sorted.end());

    // Assign plants: each student gets two cups per row (left-to-right)
    for (std::size_t i = 0; i < sorted.size(); ++i) {
        std::vector<Plants> p;
        p.reserve(4);
        const std::size_t idx = i * 2;

        if (row1.size() >= idx + 2) {
            p.push_back(from_char(row1[idx]));
            p.push_back(from_char(row1[idx + 1]));
        }
        if (row2.size() >= idx + 2) {
            p.push_back(from_char(row2[idx]));
            p.push_back(from_char(row2[idx + 1]));
        }

        assignments_.emplace(sorted[i], std::move(p));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        return {};
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const auto v = g.plants(student);
    std::array<Plants, 4> result{};
    for (std::size_t i = 0; i < 4 && i < v.size(); ++i) {
        result[i] = v[i];
    }
    return result;
}

}  // namespace kindergarten_garden
