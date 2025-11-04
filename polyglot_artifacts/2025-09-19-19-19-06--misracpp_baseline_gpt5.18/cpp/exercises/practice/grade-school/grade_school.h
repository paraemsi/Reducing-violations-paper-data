#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to the given grade.
    // Returns false if the student already exists in the roster (in any grade).
    bool add(const std::string& name, int grade);

    // Get the full roster: grades sorted ascending, students within each grade sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

    // Get the list of students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(int grade_number) const;

private:
    std::map<int, std::vector<std::string>> roster_;
    std::set<std::string> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
