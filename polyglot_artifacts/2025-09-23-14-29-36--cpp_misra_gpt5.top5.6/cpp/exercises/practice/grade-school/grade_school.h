#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include <type_traits>

namespace grade_school {

using grade_t = std::int32_t;
using roster_map_t = std::map<int, std::vector<std::string>>;

// Note: roster_map_t uses 'int' to match the public test harness type exactly.
// This is a controlled deviation necessary for interoperability with tests.
static_assert(std::is_signed<grade_t>::value, "grade_t must be signed");
static_assert(sizeof(grade_t) == sizeof(int), "grade_t must be same width as int for roster_map_t compatibility");

class school {
public:
    school() = default;

    // Add a student; returns false if the student name already exists in the roster
    bool add(const std::string& name, grade_t grade_level);

    // Get the list of students in a given grade (alphabetically sorted)
    std::vector<std::string> grade(grade_t grade_level) const;

    // Get the full roster: grades sorted ascending; students within each grade sorted alphabetically
    roster_map_t roster() const;

private:
    std::map<grade_t, std::set<std::string>> m_roster{};
    std::unordered_set<std::string> m_all_names{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
