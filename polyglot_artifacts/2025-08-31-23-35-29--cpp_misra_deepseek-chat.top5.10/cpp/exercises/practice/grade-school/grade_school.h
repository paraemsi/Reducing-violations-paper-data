#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <set>

namespace grade_school {

class school {
public:
    // Add a student to a grade
    void add(const std::string& name, std::int32_t grade);
    
    // Get all students in all grades, sorted by grade and then by name
    std::map<std::int32_t, std::vector<std::string>> roster() const;
    
    // Get all students in a specific grade, sorted alphabetically
    std::vector<std::string> grade(std::int32_t grade_num) const;
    
private:
    std::map<std::int32_t, std::vector<std::string>> students_by_grade;
    std::set<std::string> all_students;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
