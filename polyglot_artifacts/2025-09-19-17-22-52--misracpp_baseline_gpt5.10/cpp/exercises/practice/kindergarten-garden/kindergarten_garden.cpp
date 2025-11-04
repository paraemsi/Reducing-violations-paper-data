#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {
const std::vector<std::string> kStudents = {
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};
}  // namespace

garden::garden(const std::string& diagram) {
    const auto pos = diagram.find('\n');
    if (pos == std::string::npos) {
        // If only one row is provided, treat the second row as empty.
        row1_ = diagram;
        row2_.clear();
    } else {
        row1_ = diagram.substr(0, pos);
        row2_ = diagram.substr(pos + 1);
    }
    // Tolerate Windows line endings.
    if (!row1_.empty() && row1_.back() == '\r') row1_.pop_back();
    if (!row2_.empty() && row2_.back() == '\r') row2_.pop_back();
}

plant garden::map_char(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::size_t garden::student_index(const std::string& student) {
    const auto it = std::find(kStudents.begin(), kStudents.end(), student);
    if (it == kStudents.end()) {
        throw std::out_of_range("Unknown student: " + student);
    }
    return static_cast<std::size_t>(std::distance(kStudents.begin(), it));
}

std::vector<plant> garden::plants(const std::string& student) const {
    const std::size_t idx = student_index(student) * 2;

    std::vector<plant> result;
    result.reserve(4);

    if (row1_.size() < idx + 2 || row2_.size() < idx + 2) {
        throw std::out_of_range("Diagram does not contain cups for the requested student");
    }

    result.push_back(map_char(row1_[idx]));
    result.push_back(map_char(row1_[idx + 1]));
    result.push_back(map_char(row2_[idx]));
    result.push_back(map_char(row2_[idx + 1]));

    return result;
}

static constexpr Plants to_plants(plant p) noexcept {
    switch (p) {
        case plant::clover:   return Plants::clover;
        case plant::grass:    return Plants::grass;
        case plant::radishes: return Plants::radishes;
        case plant::violets:  return Plants::violets;
    }
    return Plants::clover;
}
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    const garden g(diagram);
    const auto v = g.plants(student);
    if (v.size() != 4) {
        throw std::out_of_range("Unexpected number of cups for student");
    }
    return std::array<Plants, 4>{to_plants(v[0]), to_plants(v[1]), to_plants(v[2]), to_plants(v[3])};
}

}  // namespace kindergarten_garden
