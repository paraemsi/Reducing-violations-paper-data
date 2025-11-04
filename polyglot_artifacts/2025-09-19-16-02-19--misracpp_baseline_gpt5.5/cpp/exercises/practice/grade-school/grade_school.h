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
    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, int grade);

    // Returns the full roster: grades in ascending order and names sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

    // Returns all students in the specified grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

private:
    std::map<int, std::set<std::string>> db_;
    std::set<std::string> all_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
