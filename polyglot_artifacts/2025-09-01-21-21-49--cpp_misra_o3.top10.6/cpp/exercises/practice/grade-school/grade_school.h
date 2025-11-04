#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

/* Fixed-width signed type for grade numbers (e.g. 1, 2 …) – must match
 * the signed int used in the tests so the template parameter of
 * std::map<int, …> is identical. */
using grade_t = std::int32_t;

class school {
public:
    // Add a student to a grade; duplicated names are ignored per requirements.
    void add(const std::string& name, grade_t grade_level);

    // Return the students in a single grade, alphabetically sorted.
    std::vector<std::string> grade(grade_t grade_level) const;

    // Return the entire school roster: grades ascending, names alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    // Internal storage guarantees grade order and name uniqueness + ordering.
    std::map<grade_t, std::set<std::string>> m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
