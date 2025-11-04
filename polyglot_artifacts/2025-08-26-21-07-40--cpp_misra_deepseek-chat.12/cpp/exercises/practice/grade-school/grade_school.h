#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace grade_school {

class school {
private:
    std::map<std::int32_t, std::vector<std::string>> roster_;
    std::unordered_map<std::string, std::int32_t> student_to_grade_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, std::int32_t grade);
    
    // Get all students in a grade
    std::vector<std::string> grade(std::int32_t grade) const;
    
    // Get the complete roster, sorted by grade and then by name
    std::map<std::int32_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
