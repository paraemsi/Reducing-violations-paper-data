#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
private:
    std::map<std::uint32_t, std::set<std::string>> roster_;
    std::set<std::string> all_students_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, std::uint32_t grade);
    
    // Get the roster for all grades
    std::map<std::uint32_t, std::vector<std::string>> roster() const;
    
    // Get students in a specific grade
    std::vector<std::string> grade(std::uint32_t grade_number) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
