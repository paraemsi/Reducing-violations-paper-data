#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Adds a student to a grade. Returns false if the student is already enrolled anywhere.
    bool add(const std::string& name, int grade);

    // Returns the list of students in the given grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Returns the full roster: grades in ascending order and students sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps names unique and sorted within each grade.
    std::map<int, std::set<std::string>> db_;
    // Index to ensure a student is not added more than once across the whole roster.
    std::map<std::string, int> index_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
