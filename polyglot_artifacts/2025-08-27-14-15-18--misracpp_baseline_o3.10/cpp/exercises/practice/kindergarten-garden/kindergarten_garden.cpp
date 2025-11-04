#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {


Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'R':
            return Plants::radishes;
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument{"Invalid plant code"};
    }
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    // Remove potential leading or trailing newline characters
    std::string trimmed = diagram;

    if (!trimmed.empty() && trimmed.front() == '\n') {
        trimmed.erase(trimmed.begin());
    }
    if (!trimmed.empty() && trimmed.back() == '\n') {
        trimmed.pop_back();
    }

    // Split diagram into two rows
    auto pos = trimmed.find('\n');
    if (pos == std::string::npos) {
        throw std::invalid_argument{"Diagram must contain two rows"};
    }
    std::string row1 = trimmed.substr(0, pos);
    std::string row2 = trimmed.substr(pos + 1);

    if (row1.size() != row2.size() || row1.size() % 2 != 0) {
        throw std::invalid_argument{"Rows must be of equal even length"};
    }

    // Copy and sort students for consistent ordering
    std::vector<std::string> kids = students;
    std::sort(kids.begin(), kids.end());

    std::size_t pair_count = row1.size() / 2;

    for (std::size_t i = 0; i < std::min(kids.size(), pair_count); ++i) {
        std::vector<Plants> pv{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1]),
        };
        assignments_.emplace(kids[i], std::move(pv));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        return {};
    }
    return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    if (vec.size() != 4) {
        throw std::invalid_argument{"Student not found or incorrect number of plants"};
    }
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
