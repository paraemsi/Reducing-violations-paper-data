#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

// Alias for integer type to comply with MISRA rules
using grade_t = std::int32_t;

class school {
private:
    std::map<grade_t, std::vector<std::string>> roster_;
public:
    school();
    void add(const std::string& name, int grade);
    const std::map<grade_t, std::vector<std::string>>& roster() const;
    std::vector<std::string> grade(int grade) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
