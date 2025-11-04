#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>

namespace grade_school {

 // Public API uses 'int' to match test expectations (std::map<int, ...>).
 // This is a controlled deviation from the MISRA guidance to avoid 'int' for non-main types.
using grade_t = int;
using student_list = std::vector<std::string>;
using roster_map = std::map<grade_t, student_list>;

class school {
public:
    school() noexcept = default;

    // Adds a student to a grade. Returns false if the student already exists.
    bool add(const std::string& name, grade_t grade_level) noexcept;

    // Returns the sorted list of students in the given grade.
    student_list grade(grade_t grade_level) const noexcept;

    // Returns the full roster: grades in ascending order, students alphabetically.
    roster_map roster() const noexcept;

private:
    roster_map data_{};
    std::map<std::string, grade_t> index_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
