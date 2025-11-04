#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace grade_school {

class school {
public:
    // Add a student to the specified grade.
    // Returns true if the student was added, false if the student
    // already exists anywhere in the school.
    bool add(const std::string& name, int grade);

    // Return a list of students in the given grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Return the complete roster sorted by grade, then by student name.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // grade -> ordered set of student names
    std::map<int, std::set<std::string>> m_roster;
    // Track every student to enforce uniqueness across grades
    std::set<std::string> m_all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
