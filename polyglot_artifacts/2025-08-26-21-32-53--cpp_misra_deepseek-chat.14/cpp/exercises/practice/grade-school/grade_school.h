#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
private:
    // Use a type alias for internal storage
    using GradeType = std::int32_t;
    std::map<GradeType, std::vector<std::string>> roster_;
public:
    // Add a student to a grade
    void add(const std::string& name, int grade);
    
    // Get all students in a grade
    const std::vector<std::string>& grade(int grade) const;
    
    // Get the complete school roster
    std::map<int, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
