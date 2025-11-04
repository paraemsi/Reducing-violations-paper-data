#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace grade_school {

class school {
public:
    // Add a student to a grade.
    // Returns true if the student was added; false if the student
    // is already present in any grade.
    bool add(const std::string& name, int grade);

    // Return an alphabetically-sorted list of students in the given grade.
    std::vector<std::string> grade(int grade) const;

    // Return the full roster: grades ascending, students alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // grade -> ordered unique set of student names
    std::map<int, std::set<std::string>> data_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
