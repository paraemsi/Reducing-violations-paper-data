#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_type = std::int32_t;
    using roster_type = std::map<int, std::vector<std::string>>;

    school() = default;

    // Add a student to a grade.
    // Returns true if the student was added, false if the student already exists in the roster.
    bool add(const std::string& name, grade_type grade);

    // Get a sorted list of students in a specific grade.
    std::vector<std::string> grade(grade_type grade) const;

    // Get the full roster with grades sorted ascending and names sorted alphabetically.
    roster_type roster() const;

private:
    // Internal storage keeps names sorted and unique per grade.
    std::map<grade_type, std::set<std::string>> m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
