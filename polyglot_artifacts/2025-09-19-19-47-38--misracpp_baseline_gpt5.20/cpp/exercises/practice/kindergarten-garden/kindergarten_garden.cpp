#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace kindergarten_garden {

namespace {
std::vector<std::string> default_roster() {
    return {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}

std::pair<std::string, std::string> parse_rows(const std::string& diagram) {
    auto nl = diagram.find('\n');
    if (nl == std::string::npos) {
        // If only one row provided, second row is empty.
        return {diagram, std::string{}};
    }
    return {diagram.substr(0, nl), diagram.substr(nl + 1)};
}
}  // namespace

garden::garden(const std::string& diagram) {
    std::tie(row1_, row2_) = parse_rows(diagram);
    roster_ = default_roster();
}

garden::garden(const std::string& diagram, std::vector<std::string> students) {
    std::tie(row1_, row2_) = parse_rows(diagram);
    std::sort(students.begin(), students.end());
    roster_ = std::move(students);
}

plant garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it = std::find(roster_.begin(), roster_.end(), student);
    if (it == roster_.end()) {
        return {};
    }
    std::size_t index = static_cast<std::size_t>(std::distance(roster_.begin(), it));
    std::size_t pos = index * 2;

    std::vector<plant> result;
    result.reserve(4);

    if (row1_.size() >= pos + 1) result.push_back(char_to_plant(row1_[pos]));
    if (row1_.size() >= pos + 2) result.push_back(char_to_plant(row1_[pos + 1]));
    if (row2_.size() >= pos + 1) result.push_back(char_to_plant(row2_[pos]));
    if (row2_.size() >= pos + 2) result.push_back(char_to_plant(row2_[pos + 1]));

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    auto rows = parse_rows(diagram);
    const std::string& row1 = rows.first;
    const std::string& row2 = rows.second;
    auto roster = default_roster();

    auto it = std::find(roster.begin(), roster.end(), student);
    if (it == roster.end()) {
        throw std::invalid_argument("Unknown student");
    }
    std::size_t index = static_cast<std::size_t>(std::distance(roster.begin(), it));
    std::size_t pos = index * 2;

    auto map = [](char c) -> Plants {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: throw std::invalid_argument("Unknown plant code");
        }
    };

    std::array<Plants, 4> result{
        map(row1.at(pos)),
        map(row1.at(pos + 1)),
        map(row2.at(pos)),
        map(row2.at(pos + 1))
    };
    return result;
}

}  // namespace kindergarten_garden
