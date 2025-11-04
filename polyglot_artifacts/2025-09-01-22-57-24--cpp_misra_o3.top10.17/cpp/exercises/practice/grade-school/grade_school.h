#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

// MISRA C++: introduce a project-wide alias for the integral grade type.
// Raw std::int32_t appears only here.
using grade_t = std::int32_t;

class school {
public:
    // Add a student to a grade.
    // Returns true if the student was added; false if the student
    // already exists in any grade.
    [[nodiscard]] bool add_student(const std::string& name, grade_t grade_level);
    void add(const std::string& name, grade_t grade_level);

    // Return a list of students in the given grade (alphabetically sorted).
    std::vector<std::string> grade(grade_t grade_level) const;

    // Return the complete roster: grades in ascending order, each list sorted.
    [[nodiscard]] std::map<grade_t, std::vector<std::string>>
    roster() const;

private:
    // Mapping: grade -> list of student names (kept sorted).
    std::map<grade_t, std::vector<std::string>> grade_map_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
