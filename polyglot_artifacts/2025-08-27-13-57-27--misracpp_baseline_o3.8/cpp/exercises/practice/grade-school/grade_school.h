#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace grade_school {

using roster_t = std::map<int, std::vector<std::string>>;

class school {
public:
    // Add a student to a grade.
    // Throws std::domain_error if the student already exists.
    void add(const std::string& name, int grade);

    // Return alphabetically-sorted list of students in the grade.
    std::vector<std::string> grade(int grade) const;

    // Return complete roster, grades numeric and students alphabetical.
    roster_t roster() const;

private:
    std::map<int, std::set<std::string>> by_grade_;
    std::unordered_map<std::string, int> lookup_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
