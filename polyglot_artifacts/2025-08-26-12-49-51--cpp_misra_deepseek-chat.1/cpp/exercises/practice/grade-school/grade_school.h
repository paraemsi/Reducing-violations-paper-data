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
    std::map<std::uint32_t, std::set<std::string>> roster_;
public:
    // Add a student to a grade
    void add(const std::string& name, std::uint32_t grade);
    // Get all students in a grade
    std::set<std::string> grade(std::uint32_t grade_num) const;
    // Get the complete roster sorted by grade and then by name
    std::map<std::uint32_t, std::set<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
