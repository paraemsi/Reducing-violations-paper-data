#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/* Alias used for grade identifiers to comply with MISRA C++ rules */
using grade_t  = std::int32_t;
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    /* Add a student to a grade – duplicate names are ignored. */
    void add(std::string const& name, grade_t grade);

    /* Return the complete roster, sorted by grade & then name. */
    roster_t roster() const;

    /* Return the students in one grade, sorted alphabetically. */
    std::vector<std::string> grade(grade_t grade) const;

private:
    roster_t m_roster {}; /* internal storage – always kept sorted */
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
