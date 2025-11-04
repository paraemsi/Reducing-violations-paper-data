#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const std::string& name, int grade);

    // Return a sorted vector of student names in the given grade.
    std::vector<std::string> grade(int grade) const;

    // Return a sorted vector of all students in all grades, sorted by grade then name.
    std::vector<std::string> roster() const;

private:
    // Map from grade to set of student names (set keeps names unique and sorted)
    std::map<int, std::set<std::string> > students_by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
