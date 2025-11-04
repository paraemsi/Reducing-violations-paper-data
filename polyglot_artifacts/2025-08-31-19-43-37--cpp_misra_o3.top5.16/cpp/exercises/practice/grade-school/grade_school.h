#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school final
{
public:
    using grade_t = std::int32_t;

    // Adds a student to a grade; returns false if the student already exists.
    auto add(const std::string& name, grade_t grade) -> bool;

    // Returns alphabetically-sorted students in the requested grade.
    auto grade(grade_t grade) const -> std::vector<std::string>;

    // Returns the complete roster: grades ascending, names alphabetically.
    [[nodiscard]] auto roster() const -> std::map<grade_t, std::vector<std::string>>;

private:
    // Internal storage keeps each grade’s students unique and ordered.
    std::map<grade_t, std::set<std::string>> m_data {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
