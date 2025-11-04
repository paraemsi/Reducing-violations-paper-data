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

    // Get a sorted list of students in a grade.
    std::vector<std::string> grade(int) const;

    // Get a sorted list of all students in all grades.
    std::vector<std::string> roster() const;

    // Get the full map of grades to students (for testing)
    std::map<int, std::vector<std::string>> grades() const;

private:
    // Map from grade to set of student names (sorted, unique)
    std::map<int, std::vector<std::string>> students_by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
