#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

const std::array<std::string, 12> garden::default_students_{
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : students_(default_students_.begin(), default_students_.end()) {
    // Split the diagram into two rows
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    }

    row1_ = diagram.substr(0, newline_pos);
    row2_ = diagram.substr(newline_pos + 1);

    // Remove potential carriage returns
    if (!row1_.empty() && row1_.back() == '\r') {
        row1_.pop_back();
    }
    if (!row2_.empty() && row2_.back() == '\r') {
        row2_.pop_back();
    }

    // Validate row sizes
    if (row1_.size() != row2_.size() || (row1_.size() % 2) != 0) {
        throw std::invalid_argument("each row must have the same even number of cups");
    }
    if (row1_.size() / 2 < students_.size()) {
        throw std::invalid_argument("not enough cups for the default students");
    }
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_(students) {
    // Ensure students are in alphabetical order as per assignment rules
    std::sort(students_.begin(), students_.end());

    // Split the diagram into two rows
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    }

    row1_ = diagram.substr(0, newline_pos);
    row2_ = diagram.substr(newline_pos + 1);

    // Remove potential carriage returns
    if (!row1_.empty() && row1_.back() == '\r') {
        row1_.pop_back();
    }
    if (!row2_.empty() && row2_.back() == '\r') {
        row2_.pop_back();
    }

    // Validate row sizes
    if (row1_.size() != row2_.size() || (row1_.size() % 2) != 0) {
        throw std::invalid_argument("each row must have the same even number of cups");
    }
    if (row1_.size() / 2 < students_.size()) {
        throw std::invalid_argument("not enough cups for the provided students");
    }
}

std::vector<garden::Plant> garden::plants(const std::string& student) const {
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end()) {
        throw std::invalid_argument("unknown student: " + student);
    }
    std::size_t index = static_cast<std::size_t>(std::distance(students_.begin(), it));
    std::size_t col = index * 2;

    if (col + 1 >= row1_.size()) {
        throw std::out_of_range("not enough cups for the requested student");
    }

    return {
        char_to_plant(row1_[col]),
        char_to_plant(row1_[col + 1]),
        char_to_plant(row2_[col]),
        char_to_plant(row2_[col + 1])
    };
}

garden::Plant garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument(std::string("invalid plant code: ") + c);
    }
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
