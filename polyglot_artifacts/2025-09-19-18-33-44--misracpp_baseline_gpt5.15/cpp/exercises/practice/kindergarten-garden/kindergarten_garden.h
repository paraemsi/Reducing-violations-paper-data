#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstddef>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

using student_t = std::string;
using students_t = std::vector<student_t>;

// Returns the default list of students in alphabetical order.
students_t default_students();

class garden {
public:
    explicit garden(const std::string& diagram, students_t students = default_students());
    std::vector<plant> plants(const student_t& name) const;

private:
    std::string row1_;
    std::string row2_;
    students_t students_;

    static plant from_char(char c);
    std::size_t index_of(const student_t& name) const;
};

// Free function API expected by tests.
std::array<Plants, 4> plants(const std::string& diagram, const std::string& name);

}  // namespace kindergarten_garden
