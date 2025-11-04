#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>

namespace grade_school {

class school {
private:
    std::map<int, std::vector<std::string>> roster_;
public:
    // Add a student to a grade
    void add(const std::string& name, int grade);
    // Get all students in a grade
    std::vector<std::string> grade(int grade) const;
    // Get the complete school roster
    std::map<int, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
