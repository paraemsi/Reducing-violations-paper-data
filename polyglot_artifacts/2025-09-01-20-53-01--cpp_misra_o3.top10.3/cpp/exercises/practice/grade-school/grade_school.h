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
    school() = default;

    // Add a student to a grade.
    // Throws std::domain_error if the student is already present
    // in any grade.
    auto add(const std::string& name, grade_t grade_level) -> void;

    // Return the list of students in the specified grade,
    // sorted alphabetically. If the grade has no students,
    // an empty vector is returned.
    auto grade(grade_t grade_level) const -> std::vector<std::string>;

    // Return the complete roster, keyed by grade, with every
    // student list already sorted alphabetically.
    auto roster() const -> std::map<grade_t, std::vector<std::string>>;

private:
    std::map<grade_t, std::vector<std::string>> m_roster{};
};  // class school

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
