#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

// Alias for grade type to comply with MISRA rules
using grade_t = std::uint32_t;

class school {
private:
    std::map<grade_t, std::vector<std::string>> roster_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, grade_t grade);
    
    // Get all students in a grade, returns an empty vector if the grade doesn't exist
    std::vector<std::string> grade(grade_t grade_num) const;
    
    // Get the complete school roster, sorted by grade and within grade by name
    std::map<grade_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
