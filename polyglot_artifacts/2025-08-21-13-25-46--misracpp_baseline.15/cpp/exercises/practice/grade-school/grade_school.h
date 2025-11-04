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

    // Return a sorted list of all students in a grade.
    std::vector<std::string> grade(int) const;

    // Return a sorted mapping of all grades to their students.
    std::map<int, std::vector<std::string> > roster() const;

private:
    // Map from grade to set of student names (set keeps names unique and sorted)
    std::map<int, std::set<std::string> > students_by_grade_;
    // Set of all student names (to prevent duplicates across all grades)
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
