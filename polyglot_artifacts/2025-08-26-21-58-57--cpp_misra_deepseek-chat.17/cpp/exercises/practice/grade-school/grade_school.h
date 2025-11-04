#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
private:
    std::map<std::uint32_t, std::vector<std::string>> roster_;
    std::set<std::string> all_students_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, std::uint32_t grade);
    
    // Get students in a grade, sorted alphabetically
    std::vector<std::string> grade(std::uint32_t grade_num) const;
    
    // Get all students in all grades, sorted by grade then name
    std::map<std::uint32_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
