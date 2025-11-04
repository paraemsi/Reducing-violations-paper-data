#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Fixed-width alias for grade identifiers
using grade_t = std::int32_t;

class school {
public:
    school() = default;

    // Return false if the student already exists in any grade
    bool add(const std::string& name, grade_t grade_level);

    // Return the (alphabetically) sorted list of students in a grade
    std::vector<std::string> grade(grade_t grade_level) const;

    // Return the complete roster: grades ascending, students alphabetical
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> grades_;  // internal storage
    std::set<std::string> students_;                   // quick duplicate check
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
