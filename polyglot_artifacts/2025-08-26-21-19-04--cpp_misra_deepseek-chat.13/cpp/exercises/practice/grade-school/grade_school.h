#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>

namespace grade_school {

// Alias for grade type
using grade_t = std::uint32_t;

class school {
private:
    std::map<grade_t, std::vector<std::string>> roster_;
    std::unordered_set<std::string> all_students_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, grade_t grade);
    
    // Get all students in a grade
    std::vector<std::string> grade(grade_t grade) const;
    
    // Get the complete roster, sorted by grade and then by name
    std::map<grade_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
