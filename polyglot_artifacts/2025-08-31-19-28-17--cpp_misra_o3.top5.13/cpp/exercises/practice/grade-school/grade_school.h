#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace grade_school {

class school {
 public:
    // Add a student to a grade.
    // Returns false if the student is already enrolled (in any grade),
    // true otherwise.
    auto add(const std::string& name, std::int32_t grade) -> bool;

    // Return the complete roster.
    // Grades are ordered 1, 2, 3, … and students within a grade
    // are returned in alphabetical order.
    auto roster() const -> std::vector<std::string>;

    // Return the list of students in a single grade, alphabetically sorted.
    auto grade(std::int32_t grade) const -> std::vector<std::string>;

 private:
    std::map<std::int32_t, std::set<std::string>> grade_to_names_;
    std::unordered_map<std::string, std::int32_t> student_to_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
