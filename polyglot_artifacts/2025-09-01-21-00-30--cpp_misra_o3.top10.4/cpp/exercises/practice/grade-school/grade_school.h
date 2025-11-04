#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_t = int;

    // Add a student to a grade.
    // Returns true if the student was added, false when the student
    // already exists in any grade.
    bool add(std::string_view name, grade_t level);

    // Obtain the full roster: grades in ascending order, students
    // alphabetically within each grade.
    [[nodiscard]] std::map<grade_t, std::vector<std::string>> roster() const;

    // Obtain the list of students for a single grade.
    std::vector<std::string> grade(grade_t level) const;

private:
    // Internal storage: keeps students unique and ordered.
    std::map<grade_t, std::set<std::string>> m_roster{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
