#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

// Alias for grade type to comply with MISRA rules
using grade_t = std::uint32_t;

class school {
private:
    std::map<grade_t, std::vector<std::string>> roster_;
public:
    void add(const std::string& name, grade_t grade);
    const std::map<grade_t, std::vector<std::string>>& roster() const;
    std::vector<std::string> grade(grade_t grade_num) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
