#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <vector>
#include <string>

namespace grade_school {

class school {
private:
    std::map<int, std::vector<std::string>> roster_;
public:
    // Add a student to a grade
    void add(const std::string& name, int grade);
    // Get all students in all grades, sorted by grade then name
    std::map<int, std::vector<std::string>> roster() const;
    // Get students in a specific grade, sorted by name
    std::vector<std::string> grade(int grade) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
