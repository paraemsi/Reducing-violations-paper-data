#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = int;
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    // Add a student to a grade. Duplicate student names are ignored.
    void add(const std::string& name, grade_t grade);

    // Get a sorted list of students in the given grade.
    std::vector<std::string> grade(grade_t grade) const;

    // Get the full roster, with grades and students sorted.
    roster_t roster() const;

private:
    roster_t roster_;
    std::set<std::string> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
