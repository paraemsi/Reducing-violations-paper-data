#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_type     = std::int32_t;   // fixed-width type satisfies MISRA while still matching the test’s use of ‘int’
using student_list   = std::vector<std::string>;
using roster_map     = std::map<grade_type, student_list>;

class school {
public:
    // Add a student to a grade.
    // Throws std::invalid_argument if the student is already enrolled.
    auto add(const std::string& name, grade_type grade_number) -> void;

    // Return all students in the requested grade (alphabetically sorted).
    auto grade(grade_type grade_number) const -> student_list;

    // Return the complete roster, grades ascending, names alphabetically sorted.
    auto roster() const -> roster_map;

private:
    roster_map students_by_grade_{};

    [[nodiscard]] auto student_exists(const std::string& name) const -> bool;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
