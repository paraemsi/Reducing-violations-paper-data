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
    // Add a student to a grade. Returns true if the student was added,
    // false if the student is already enrolled in any grade.
    bool add(const std::string& name, int g);

    // Get a sorted list of students in a specific grade.
    std::vector<std::string> grade(int g) const;

    // Get the full roster: grades in ascending order with students sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<int, std::set<std::string>> by_grade_;
    std::unordered_map<std::string, int> enrollment_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
