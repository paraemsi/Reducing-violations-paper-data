#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Adds a student to the given grade.
    // Returns false if the student already exists in the roster (any grade).
    bool add(const std::string& name, int grade);

    // Returns the full roster with grades in ascending order and names alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

    // Returns the list of students in the specified grade, alphabetically sorted.
    std::vector<std::string> grade(int grade) const;

private:
    // Internal storage uses set to keep names unique and sorted within a grade.
    std::map<int, std::set<std::string>> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
