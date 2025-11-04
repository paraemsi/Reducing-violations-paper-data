#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    // Adds a student to a grade.
    // Returns true if the student was added, false if the student already exists.
    bool add(const std::string& name, grade_t grade_level);

    // Retrieves a sorted list of students in the specified grade.
    std::vector<std::string> grade(grade_t grade_level) const;

    // Retrieves the complete, sorted school roster.
    [[nodiscard]] std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::vector<std::string>> roster_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
