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
    // Returns true if the student was added; false if the student
    // already exists in any grade.
    bool add(const std::string& name, int grade);

    // Return all students in the specified grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Return the complete roster, sorted by grade then alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage ensures uniqueness and keeps names sorted.
    std::map<int, std::set<std::string>> roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
