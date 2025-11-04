#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    // Attempts to add a student to the given grade.
    // Returns true if the student was added, false if the student
    // already exists in the school.
    bool add(const std::string& name, grade_t grade);

    // Returns the complete roster, keyed by grade with the students
    // in each grade sorted alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

    // Returns the list of students for the specified grade,
    // sorted alphabetically.
    std::vector<std::string> grade(grade_t grade) const;

private:
    // Internal storage keeps names sorted automatically via std::set.
    std::map<grade_t, std::set<std::string>> m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
