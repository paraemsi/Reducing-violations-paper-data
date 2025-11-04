#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <set>

namespace grade_school {

class school {
private:
    std::map<std::uint32_t, std::vector<std::string>> roster_;
    std::set<std::string> all_students_;
public:
    // Add a student to a grade
    void add(const std::string& name, std::uint32_t grade);
    // Get the roster which is a map of grade to vector of names
    std::map<std::uint32_t, std::vector<std::string>> roster() const;
    // Get students in a specific grade
    std::vector<std::string> grade(std::uint32_t grade_num) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
