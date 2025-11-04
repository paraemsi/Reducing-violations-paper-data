#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Adds a student to the specified grade.
    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, int grade);

    // Returns the list of students in the specified grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Returns the full roster: grades in ascending order and students alphabetically within each grade.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students sorted and unique per grade.
    std::map<int, std::set<std::string>> data_;
    // Tracks all student names to ensure uniqueness across the entire school.
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
