#include "kindergarten_garden.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

students_t default_students() {
    return {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}

static void parse_rows(const std::string& diagram, std::string& row1, std::string& row2) {
    std::string diag = diagram;
    if (!diag.empty() && diag.front() == '\n') {
        diag.erase(0, 1);
    }
    auto pos = diag.find('\n');
    if (pos == std::string::npos) {
        row1 = diag;
        row2.clear();
        return;
    }
    row1 = diag.substr(0, pos);
    auto pos2 = diag.find('\n', pos + 1);
    if (pos2 == std::string::npos) {
        row2 = diag.substr(pos + 1);
    } else {
        row2 = diag.substr(pos + 1, pos2 - (pos + 1));
    }
}

garden::garden(const std::string& diagram, students_t students)
    : row1_(), row2_(), students_(std::move(students)) {
    // Normalize and parse the diagram into two rows
    parse_rows(diagram, row1_, row2_);

    // Assign cups in alphabetical order of students
    std::sort(students_.begin(), students_.end());
}

std::size_t garden::index_of(const student_t& name) const {
    auto it = std::find(students_.begin(), students_.end(), name);
    if (it == students_.end()) {
        return students_.size();
    }
    return static_cast<std::size_t>(std::distance(students_.begin(), it));
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

std::vector<plant> garden::plants(const student_t& name) const {
    std::vector<plant> result;
    auto idx = index_of(name);
    if (idx >= students_.size()) {
        return result;
    }
    auto col = idx * 2;

    if (row1_.size() >= col + 2) {
        result.push_back(from_char(row1_[col]));
        result.push_back(from_char(row1_[col + 1]));
    }
    if (row2_.size() >= col + 2) {
        result.push_back(from_char(row2_[col]));
        result.push_back(from_char(row2_[col + 1]));
    }

    return result;
}

// Free function expected by tests.
std::array<Plants, 4> plants(const std::string& diagram, const std::string& name) {
    garden g(diagram);
    auto vec = g.plants(name);
    std::array<Plants, 4> out{};
    for (std::size_t i = 0; i < vec.size() && i < out.size(); ++i) {
        out[i] = vec[i];
    }
    return out;
}

}  // namespace kindergarten_garden
