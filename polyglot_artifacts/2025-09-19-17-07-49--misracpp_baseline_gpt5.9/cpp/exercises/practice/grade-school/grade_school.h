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
    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, int g);

    // Get a sorted list of students in the specified grade.
    std::vector<std::string> grade(int g) const;

    // Get the full roster: grades in ascending order; students within each grade sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students unique and sorted within each grade.
    std::map<int, std::set<std::string>> grades_;
    // Tracks all students to prevent duplicates across the entire roster.
    std::set<std::string> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
