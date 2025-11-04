#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Project-specific alias for grade identifiers; kept as int to match tests,
// but used via alias to follow MISRA guidance on avoiding plain integer names in interfaces.
using grade_t = int;

class school {
public:
    bool add(const std::string& name, grade_t grade);
    std::map<grade_t, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(grade_t grade) const;

private:
    std::map<grade_t, std::set<std::string>> by_grade_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
