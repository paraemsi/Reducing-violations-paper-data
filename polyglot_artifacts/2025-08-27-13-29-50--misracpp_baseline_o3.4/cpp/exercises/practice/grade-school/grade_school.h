#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// A simple container that tracks students and their grades.
class school {
public:
    // Add a student to a grade. If the student already exists anywhere in the
    // roster the call is ignored.
    void add(const std::string& name, int grade);

    // Return the list of students in the requested grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Return the complete roster: grades in numeric order, each student list
    // sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal data: grade → unique, alphabetically ordered set of names.
    std::map<int, std::set<std::string>> m_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
