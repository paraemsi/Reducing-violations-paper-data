#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

using grade_t = std::int32_t;

class school {
private:
    std::map<grade_t, std::vector<std::string>> roster_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, grade_t grade);
    
    // Get all students in a grade, sorted alphabetically
    std::vector<std::string> grade(grade_t grade_num) const;
    
    // Get the complete school roster, sorted by grade and then by name
    std::map<grade_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
