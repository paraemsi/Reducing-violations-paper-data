#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school
{
public:
    // Add a student to a grade – returns false if the student already exists.
    auto add(const std::string& name, grade_t grade) -> bool;

    // Get the sorted list of students in a grade.
    auto grade(grade_t grade) const -> std::vector<std::string>;

    // Get the full roster, sorted by grade and then by student name.
    auto roster() const -> std::map<grade_t, std::vector<std::string>>;

private:
    std::map<grade_t, std::vector<std::string>> m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
