#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade. If the student already exists in the roster,
    // the request is ignored to maintain uniqueness.
    void add(const std::string& name, int g);

    // Get a sorted list of all students in a given grade.
    std::vector<std::string> grade(int g) const;

    // Get the full roster: grades sorted ascending, students alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students sorted within each grade.
    std::map<int, std::set<std::string>> by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
