#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Represents the entire school roster.
class school {
public:
    // Add a student to a grade. If the student is already present in that
    // grade (or anywhere in the school), the request is ignored.
    void add(const std::string& name, int grade);

    // Return all students in the specified grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Return the full school roster. Grades are ordered numerically and
    // students alphabetically within each grade.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students unique and sorted.
    std::map<int, std::set<std::string>> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
