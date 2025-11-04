#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student's name to the roster for a grade.
    // A student may appear at most once in the entire school.
    void add(const std::string& name, int grade);

    // Get the list of all students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Get the full roster: grades in ascending order; students in each grade alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<int, std::vector<std::string>> m_roster;
    std::unordered_set<std::string> m_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
