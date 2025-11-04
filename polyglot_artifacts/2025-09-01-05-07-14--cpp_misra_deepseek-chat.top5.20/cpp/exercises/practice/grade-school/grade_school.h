#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <set>

namespace grade_school {

class school {
private:
    std::map<std::uint32_t, std::vector<std::string>> roster_;
    std::set<std::string> all_students_;
public:
    school() = default;
    
    // Add a student to a grade
    void add(const std::string& name, std::uint32_t grade);
    
    // Get all students in a grade
    std::vector<std::string> grade(std::uint32_t grade) const;
    
    // Get the complete roster
    std::map<std::uint32_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
