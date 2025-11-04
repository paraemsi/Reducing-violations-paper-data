#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;     // tests use signed int keys; int32_t is typedef to int

class school {
public:
    /* Adds a student to the given grade.
       Returns false if the student already exists. */
    bool add(const std::string& name, grade_t grade_level);

    // Returns the students in the given grade, sorted alphabetically.
    std::vector<std::string> grade(grade_t grade_level) const;

    // Returns the full roster.
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> m_roster{};  // grade -> ordered set of names
    std::set<std::string> m_all_students{};               // global uniqueness check
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
