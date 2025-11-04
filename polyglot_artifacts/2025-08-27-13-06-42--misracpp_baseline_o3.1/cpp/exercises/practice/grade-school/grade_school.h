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
    // Returns true if the student was successfully added,
    // false if the student already exists in any grade.
    bool add(const std::string& name, int grade_level);

    // Return an alphabetically-sorted list of students in the requested grade.
    std::vector<std::string> grade(int grade_level) const;

    // Return the entire school roster:
    // grades in numerical order, students in alphabetical order.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students unique and automatically sorted.
    std::map<int, std::set<std::string>> students_by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
