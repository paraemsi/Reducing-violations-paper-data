#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_type = std::int32_t;

class school {
public:
    void add(const std::string& name, grade_type grade_level);
    std::map<grade_type, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(grade_type grade_level) const;

private:
    std::map<grade_type, std::vector<std::string>> roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
