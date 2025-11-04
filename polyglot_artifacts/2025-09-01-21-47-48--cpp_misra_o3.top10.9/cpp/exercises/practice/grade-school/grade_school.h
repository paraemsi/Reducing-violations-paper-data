#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

// Manages the roster of a small grade-school.
class school
{
public:
    // Add a student to a grade.
    // Returns false if the student already exists in any grade.
    bool add(const std::string& name, grade_t grade_id);

    // Get the list of students in a specific grade (alphabetically sorted).
    std::vector<std::string> grade(grade_t grade_id) const;

    // Get the full roster: grade -> students (all sorted).
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    // Internal storage
    std::map<grade_t, std::set<std::string>> m_grades_{};
    std::set<std::string> m_all_students_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
