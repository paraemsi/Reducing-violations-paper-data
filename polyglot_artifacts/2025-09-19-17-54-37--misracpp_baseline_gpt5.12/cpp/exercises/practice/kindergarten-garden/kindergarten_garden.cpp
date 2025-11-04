#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
    const std::vector<std::string> default_students{
        "Alice","Bob","Charlie","David","Eve","Fred","Ginny",
        "Harriet","Ileana","Joseph","Kincaid","Larry"
    };

    inline plant char_to_plant(char c) {
        switch (c) {
            case 'C': return plant::clover;
            case 'G': return plant::grass;
            case 'R': return plant::radishes;
            case 'V': return plant::violets;
            default: throw std::invalid_argument("Unknown plant code");
        }
    }

    std::vector<std::string> split_rows(const std::string& diagram) {
        std::vector<std::string> rows;
        std::string current;
        for (char ch : diagram) {
            if (ch == '\r') {
                continue; // ignore carriage returns (Windows line endings)
            } else if (ch == '\n') {
                rows.push_back(current);
                current.clear();
            } else {
                current.push_back(ch);
            }
        }
        if (!current.empty()) {
            rows.push_back(current);
        }
        return rows;
    }
}

garden::garden(const std::string& diagram)
    : garden(diagram, default_students) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students) {
    rows_ = split_rows(diagram);
    if (rows_.size() != 2) {
        throw std::invalid_argument("Diagram must have exactly two rows");
    }

    // initialize students: sorted alphabetically
    students_ = students;
    std::sort(students_.begin(), students_.end());
    index_by_student_.clear();
    for (std::size_t i = 0; i < students_.size(); ++i) {
        index_by_student_[students_[i]] = i;
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it = index_by_student_.find(student);
    if (it == index_by_student_.end()) {
        throw std::invalid_argument("Unknown student");
    }
    std::size_t idx = it->second;
    std::size_t pos = idx * 2;

    std::vector<plant> result;
    result.reserve(4);
    if (pos + 1 >= rows_[0].size() || pos + 1 >= rows_[1].size()) {
        throw std::out_of_range("Diagram doesn't have enough cups for this student");
    }
    result.push_back(char_to_plant(rows_[0][pos]));
    result.push_back(char_to_plant(rows_[0][pos + 1]));
    result.push_back(char_to_plant(rows_[1][pos]));
    result.push_back(char_to_plant(rows_[1][pos + 1]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    auto v = g.plants(student);
    if (v.size() != 4) {
        throw std::runtime_error("Unexpected number of plants for student");
    }
    std::array<Plants, 4> out{{
        static_cast<Plants>(v[0]),
        static_cast<Plants>(v[1]),
        static_cast<Plants>(v[2]),
        static_cast<Plants>(v[3]),
    }};
    return out;
}

}  // namespace kindergarten_garden
