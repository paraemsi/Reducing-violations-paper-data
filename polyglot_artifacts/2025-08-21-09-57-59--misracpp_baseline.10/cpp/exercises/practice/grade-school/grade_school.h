#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace grade_school {

class school {
public:
    // Add a student to a grade. Returns true if added, false if student already exists.
    bool add(const std::string& name, int grade);

    // Get a sorted list of students in a grade.
    std::vector<std::string> grade(int) const;

    // Get a sorted list of all students in all grades, grouped by grade.
    std::map<int, std::vector<std::string> > roster() const;

private:
    // Map from grade to set of student names (set keeps names unique and sorted)
    std::map<int, std::set<std::string>> m_students;
    // Set of all student names for uniqueness check
    std::set<std::string> m_all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
