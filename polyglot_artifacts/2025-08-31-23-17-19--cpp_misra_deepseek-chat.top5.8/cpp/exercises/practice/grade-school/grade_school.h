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
    // Alias for grade type
    using grade_t = std::uint32_t;
    
private:
    std::map<grade_t, std::set<std::string>> roster_;
    std::map<std::string, grade_t> student_grades_;
    
public:
    school() = default;
    
    void add(const std::string& name, grade_t grade);
    std::map<grade_t, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(grade_t grade_num) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
