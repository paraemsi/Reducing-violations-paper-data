#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
public:
    // Add a student to a grade
    void add(const std::string& name, std::int32_t grade);
    
    // Get all students in all grades, sorted by grade then name
    std::map<std::int32_t, std::vector<std::string>> roster() const;
    
    // Get all students in a specific grade, sorted by name
    std::vector<std::string> grade(std::int32_t grade_number) const;
    
private:
    std::map<std::int32_t, std::vector<std::string>> students_by_grade;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
