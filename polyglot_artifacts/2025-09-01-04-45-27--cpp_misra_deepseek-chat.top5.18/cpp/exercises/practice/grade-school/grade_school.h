#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include <cstdint>

namespace grade_school {

class school {
private:
    std::map<std::int32_t, std::set<std::string>> roster_;
    std::map<std::string, std::int32_t> student_to_grade_;
    
public:
    // Add a student to a grade
    void add(const std::string& name, std::int32_t grade);
    
    // Get all students in a grade
    std::vector<std::string> grade(std::int32_t grade_num) const;
    
    // Get the complete school roster
    std::map<std::int32_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
