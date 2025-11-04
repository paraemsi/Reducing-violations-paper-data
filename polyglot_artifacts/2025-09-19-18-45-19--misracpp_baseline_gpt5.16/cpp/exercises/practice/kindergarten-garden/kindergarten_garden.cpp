#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

namespace {
std::vector<std::string> default_students() {
    return {"Alice", "Bob",    "Charlie", "David",
            "Eve",   "Fred",   "Ginny",   "Harriet",
            "Ileana","Joseph", "Kincaid", "Larry"};
}

std::pair<std::string, std::string> split_rows(const std::string& diagram) {
    const auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        return {diagram, std::string{}};
    }
    return {diagram.substr(0, pos), diagram.substr(pos + 1)};
}
inline Plants to_plants(plant p) {
    switch (p) {
        case plant::clover:   return Plants::clover;
        case plant::grass:    return Plants::grass;
        case plant::radishes: return Plants::radishes;
        case plant::violets:  return Plants::violets;
    }
    throw std::invalid_argument("Unknown plant enum");
}
}  // namespace

garden::garden(const std::string& diagram) {
    auto rows = split_rows(diagram);
    row1_ = std::move(rows.first);
    row2_ = std::move(rows.second);
    students_ = default_students();
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    auto rows = split_rows(diagram);
    row1_ = std::move(rows.first);
    row2_ = std::move(rows.second);
    students_ = students;
    std::sort(students_.begin(), students_.end());
}

plant garden::decode(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        return {};
    }

    const std::size_t idx = static_cast<std::size_t>(std::distance(students_.begin(), it));
    const std::size_t p = idx * 2;

    std::vector<plant> result;
    result.reserve(4);

    if (p < row1_.size())   result.push_back(decode(row1_[p]));
    if (p + 1 < row1_.size()) result.push_back(decode(row1_[p + 1]));
    if (p < row2_.size())   result.push_back(decode(row2_[p]));
    if (p + 1 < row2_.size()) result.push_back(decode(row2_[p + 1]));

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto v = g.plants(student);
    if (v.size() != 4) {
        throw std::invalid_argument("Expected exactly four plants for student");
    }
    return {to_plants(v[0]), to_plants(v[1]), to_plants(v[2]), to_plants(v[3])};
}

}  // namespace kindergarten_garden
