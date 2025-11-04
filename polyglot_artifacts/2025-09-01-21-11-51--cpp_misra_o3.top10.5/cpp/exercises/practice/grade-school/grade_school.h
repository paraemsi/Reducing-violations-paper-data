#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school
{
public:
    school() = default;

    /* Adds a student to a grade.
       Returns false if the student is already present anywhere in the school. */
    bool add(const std::string& name, grade_t grade_level);

    /* Returns the list of students in the given grade, sorted alphabetically. */
    std::vector<std::string> grade(grade_t grade_level) const;

    /* Returns the complete roster, sorted by grade (ascending) and then by name. */
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::vector<std::string>> roster_;
    std::unordered_map<std::string, grade_t> name_index_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
