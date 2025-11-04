#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_t = std::int32_t;
    using roster_t = std::map<grade_t, std::vector<std::string>>;

    school() = default;
    ~school() = default;

    school(const school&) = default;
    school(school&&) noexcept = default;
    school& operator=(const school&) = default;
    school& operator=(school&&) noexcept = default;

    bool add(const std::string& student_name, grade_t grade_value);
    roster_t roster() const;
    std::vector<std::string> grade(grade_t grade_value) const;

private:
    roster_t roster_{};
    std::set<std::string> names_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
