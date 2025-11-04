#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>

namespace grade_school {

class school {
public:
    // Add a student to a grade. Returns true if added, false if already present.
    bool add(const std::string& name, int grade);

    // Get a sorted list of all students in a grade.
    std::vector<std::string> grade(int grade) const;

    // Get a sorted roster of all students in all grades.
    std::map<int, std::vector<std::string> > roster() const;

private:
    std::map<int, std::vector<std::string> > m_roster;
    std::map<std::string, int> m_student_grade; // To prevent duplicate students
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
