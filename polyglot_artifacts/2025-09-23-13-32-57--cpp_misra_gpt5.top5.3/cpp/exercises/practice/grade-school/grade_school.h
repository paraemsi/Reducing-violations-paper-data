#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    school() = default;

    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, grade_t grade_level);

    // Returns a sorted list of students in the requested grade (alphabetical).
    std::vector<std::string> grade(grade_t grade_level) const;

    // Returns the full roster: grades sorted ascending, students within each grade sorted alphabetically.
    roster_t roster() const;

private:
    roster_t m_roster{};
    std::unordered_set<std::string> m_students{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
