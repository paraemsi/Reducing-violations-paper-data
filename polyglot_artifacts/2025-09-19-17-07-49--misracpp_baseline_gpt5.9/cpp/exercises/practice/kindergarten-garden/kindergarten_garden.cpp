#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

garden::garden(const std::string& diagram) {
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        // If only one line is provided, treat second row as empty.
        row1_ = diagram;
        row2_.clear();
    } else {
        row1_ = diagram.substr(0, newline_pos);
        row2_ = diagram.substr(newline_pos + 1);
    }

    // Trim possible carriage returns at line ends (in case of CRLF input).
    if (!row1_.empty() && row1_.back() == '\r') row1_.pop_back();
    if (!row2_.empty() && row2_.back() == '\r') row2_.pop_back();
}

std::vector<plant> garden::plants(const std::string& student) const {
    const auto idx = student_index(student);
    const auto offset = static_cast<std::size_t>(2 * idx);

    if (row1_.size() < offset + 2 || row2_.size() < offset + 2) {
        throw std::out_of_range("Diagram does not contain enough cups for the requested student");
    }

    return {
        from_char(row1_[offset]),
        from_char(row1_[offset + 1]),
        from_char(row2_[offset]),
        from_char(row2_[offset + 1])
    };
}

const std::vector<std::string>& garden::default_students() {
    static const std::vector<std::string> students{
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    return students;
}

std::size_t garden::student_index(const std::string& name) {
    const auto& students = default_students();
    const auto it = std::find(students.begin(), students.end(), name);
    if (it == students.end()) {
        throw std::out_of_range("Unknown student name: " + name);
    }
    return static_cast<std::size_t>(std::distance(students.begin(), it));
}

plant garden::from_char(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default:
            throw std::invalid_argument("Unknown plant code");
    }
}

static Plants to_Plants(plant p) {
    switch (p) {
        case plant::clover:   return Plants::clover;
        case plant::grass:    return Plants::grass;
        case plant::radishes: return Plants::radishes;
        case plant::violets:  return Plants::violets;
    }
    return Plants::clover;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const auto v = g.plants(student);
    return { to_Plants(v[0]), to_Plants(v[1]), to_Plants(v[2]), to_Plants(v[3]) };
}

}  // namespace kindergarten_garden
