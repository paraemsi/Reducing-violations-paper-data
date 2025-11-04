#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade.
    // Returns false if the student already exists in any grade.
    bool add(const std::string& name, int grade_level);

    // Return an alphabetically-sorted list of students in the given grade.
    std::vector<std::string> grade(int grade_level) const;

    // Return the full roster: grades in numeric order, students alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<int, std::set<std::string>> m_roster;        // grade -> ordered unique students
    std::unordered_map<std::string, int> m_student_grade; // student -> grade (for duplicate check)
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
