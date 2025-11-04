#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    void add(const std::string& name, grade_t grade_level);
    std::vector<std::string> grade(grade_t grade_level) const;
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::vector<std::string>> roster_;
    bool contains_student(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
