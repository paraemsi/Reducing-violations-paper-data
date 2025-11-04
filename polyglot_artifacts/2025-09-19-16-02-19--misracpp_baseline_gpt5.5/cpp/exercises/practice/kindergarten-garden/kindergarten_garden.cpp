#include "kindergarten_garden.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

const std::vector<std::string>& garden::default_students() {
    static const std::vector<std::string> kDefault{
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    return kDefault;
}

static std::string rstrip_cr(std::string s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
    return s;
}

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_(students) {
    auto nl = diagram.find('\n');
    row1_ = rstrip_cr(diagram.substr(0, nl));
    if (nl != std::string::npos) {
        row2_ = rstrip_cr(diagram.substr(nl + 1));
    } else {
        row2_.clear();
    }
    std::sort(students_.begin(), students_.end());
}

std::size_t garden::index_for_student(const std::string& student) const {
    auto it = std::lower_bound(students_.begin(), students_.end(), student);
    if (it != students_.end() && *it == student) {
        return static_cast<std::size_t>(std::distance(students_.begin(), it));
    }
    return static_cast<std::size_t>(-1); // npos sentinel
}

plant garden::from_char(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    std::vector<plant> result;
    std::size_t idx = index_for_student(student);
    if (idx == static_cast<std::size_t>(-1)) {
        return result;
    }
    std::size_t col = idx * 2;

    if (row1_.size() <= col + 1 || row2_.size() <= col + 1) {
        return result;
    }

    result.reserve(4);
    result.push_back(from_char(row1_[col]));
    result.push_back(from_char(row1_[col + 1]));
    result.push_back(from_char(row2_[col]));
    result.push_back(from_char(row2_[col + 1]));
    return result;
}

static inline Plants to_plants(plant p) {
    switch (p) {
        case plant::grass: return Plants::grass;
        case plant::clover: return Plants::clover;
        case plant::radishes: return Plants::radishes;
        case plant::violets: return Plants::violets;
    }
    return Plants::grass; // Unreachable, silences some compilers' warnings
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    std::array<Plants, 4> out{};
    if (vec.size() == 4) {
        out[0] = to_plants(vec[0]);
        out[1] = to_plants(vec[1]);
        out[2] = to_plants(vec[2]);
        out[3] = to_plants(vec[3]);
    }
    return out;
}

}  // namespace kindergarten_garden
