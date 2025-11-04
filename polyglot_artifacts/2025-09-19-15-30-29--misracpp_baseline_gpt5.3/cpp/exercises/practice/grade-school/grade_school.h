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
    // Returns false if the student already exists anywhere in the roster.
    bool add(const std::string& name, int grade);

    // Students in a specific grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Full roster: grades in ascending order; names within each grade sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps names unique and sorted within each grade.
    std::map<int, std::set<std::string>> data_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
