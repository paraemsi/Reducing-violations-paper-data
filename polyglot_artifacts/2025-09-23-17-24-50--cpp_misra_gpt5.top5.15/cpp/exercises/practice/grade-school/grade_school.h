#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    // Add a student to a grade; returns false if the student already exists in the roster
    bool add(const std::string& name, grade_t grade_number) noexcept;

    // Get a sorted list of all students in a specific grade
    std::vector<std::string> grade(grade_t grade_number) const noexcept;

    // Get the full roster: grades in ascending order and students alphabetically
    std::map<grade_t, std::vector<std::string>> roster() const noexcept;

private:
    std::map<grade_t, std::vector<std::string>> m_roster;
    std::unordered_set<std::string> m_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
