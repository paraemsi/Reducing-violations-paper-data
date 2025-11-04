#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    school() = default;

    void add(const std::string& student, grade_t grade_value);

    std::vector<std::string> grade(grade_t grade_value) const;

    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> grade_to_students_{};
    std::set<std::string> all_students_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
