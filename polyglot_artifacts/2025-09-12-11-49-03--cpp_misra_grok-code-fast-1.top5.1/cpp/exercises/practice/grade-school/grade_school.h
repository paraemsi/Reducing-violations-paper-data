#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    bool add(const std::string& name, grade_t grade);
    std::vector<std::string> grade(grade_t grade) const;
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> grades_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
