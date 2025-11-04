#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

/*  MISRA-C++ : use an alias instead of raw 'int'  */
using grade_t = int;

namespace grade_school {

class school {
public:
    school() = default;

    /* Adds a student to a grade.
       Duplicate student names are ignored. */
    void add(const std::string& name, grade_t grade_level);

    /* Returns the complete roster. */
    std::map<grade_t, std::vector<std::string>> roster() const;

    /* Returns the list of students for a single grade. */
    std::vector<std::string> grade(grade_t grade_level) const;

private:
    std::map<grade_t, std::vector<std::string>> m_roster;

    static void insert_sorted(std::vector<std::string>& vec,
                              const std::string&                name);
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
