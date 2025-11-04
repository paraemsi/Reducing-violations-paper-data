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
    std::map<std::uint16_t, std::vector<std::string>> roster_;
    std::set<std::string> all_students_;
public:
    // Add a student to a grade
    void add(const std::string& name, std::uint16_t grade);
    
    // Get all students in a grade
    std::vector<std::string> grade(std::uint16_t grade) const;
    
    // Get the complete roster, sorted by grade and then by name
    std::map<std::uint16_t, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
