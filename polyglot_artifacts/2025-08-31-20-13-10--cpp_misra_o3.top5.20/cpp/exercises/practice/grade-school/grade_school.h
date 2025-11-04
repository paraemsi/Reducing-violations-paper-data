#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;   // fixed-width signed type permitted by MISRA

class school
{
public:
    auto add(std::string const& name, grade_t grade) -> void;

    [[nodiscard]] auto roster() const -> std::map<grade_t, std::vector<std::string>>;

    auto grade(grade_t grade) const -> std::vector<std::string>;

private:
    std::map<grade_t, std::set<std::string>> m_data {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
