#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade.
    // If the student already exists in any grade, the request is ignored.
    bool add(const std::string& name, int grade_level);

    // Get the full roster: grades in ascending order, students alphabetically within each grade.
    std::map<int, std::vector<std::string>> roster() const;

    // Get all students in a specific grade, alphabetically sorted.
    std::vector<std::string> grade(int grade_level) const;

private:
    // Internal storage keeps names unique and sorted per grade.
    std::map<int, std::set<std::string>> students_by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
