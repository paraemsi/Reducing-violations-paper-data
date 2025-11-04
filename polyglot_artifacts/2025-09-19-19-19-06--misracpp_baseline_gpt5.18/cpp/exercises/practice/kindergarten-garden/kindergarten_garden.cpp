#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
const std::vector<std::string>& default_students() {
    static const std::vector<std::string> students = {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
    return students;
}

int student_index(const std::vector<std::string>& students, const std::string& name) {
    auto it = std::find(students.begin(), students.end(), name);
    if (it == students.end()) {
        return -1;
    }
    return static_cast<int>(it - students.begin());
}

plant char_to_plant(char c) {
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

}  // namespace

garden::garden(const std::string& diagram) : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    // Split the diagram into rows (expecting two rows)
    std::size_t pos = diagram.find('\n');
    if (pos == std::string::npos) {
        rows_.push_back(diagram);
        rows_.push_back(std::string{});
    } else {
        rows_.push_back(diagram.substr(0, pos));
        // Handle possible trailing newline
        std::size_t next_start = pos + 1;
        std::size_t next_pos = diagram.find('\n', next_start);
        if (next_pos == std::string::npos) {
            rows_.push_back(diagram.substr(next_start));
        } else {
            rows_.push_back(diagram.substr(next_start, next_pos - next_start));
        }
    }

    students_ = students;
    std::sort(students_.begin(), students_.end());
}

std::vector<plant> garden::plants(const std::string& student) const {
    int idx = student_index(students_, student);
    if (idx < 0) {
        throw std::out_of_range("Unknown student name");
    }
    if (rows_.size() < 2) {
        throw std::logic_error("Diagram must contain two rows");
    }

    std::size_t offset = static_cast<std::size_t>(idx) * 2;
    if (rows_[0].size() < offset + 2 || rows_[1].size() < offset + 2) {
        throw std::out_of_range("Diagram does not have enough cups for the student");
    }

    std::vector<plant> result;
    result.reserve(4);
    result.push_back(char_to_plant(rows_[0][offset]));
    result.push_back(char_to_plant(rows_[0][offset + 1]));
    result.push_back(char_to_plant(rows_[1][offset]));
    result.push_back(char_to_plant(rows_[1][offset + 1]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    // Split the diagram into rows (expecting two rows)
    std::size_t pos = diagram.find('\n');
    std::string row1;
    std::string row2;
    if (pos == std::string::npos) {
        row1 = diagram;
        row2 = std::string{};
    } else {
        row1 = diagram.substr(0, pos);
        // Handle possible trailing newline
        std::size_t next_start = pos + 1;
        std::size_t next_pos = diagram.find('\n', next_start);
        if (next_pos == std::string::npos) {
            row2 = diagram.substr(next_start);
        } else {
            row2 = diagram.substr(next_start, next_pos - next_start);
        }
    }

    const auto& students = default_students();
    int idx = student_index(students, student);
    if (idx < 0) {
        throw std::out_of_range("Unknown student name");
    }

    std::size_t offset = static_cast<std::size_t>(idx) * 2;
    if (row1.size() < offset + 2 || row2.size() < offset + 2) {
        throw std::out_of_range("Diagram does not have enough cups for the student");
    }

    return {char_to_plant(row1[offset]),
            char_to_plant(row1[offset + 1]),
            char_to_plant(row2[offset]),
            char_to_plant(row2[offset + 1])};
}

}  // namespace kindergarten_garden
