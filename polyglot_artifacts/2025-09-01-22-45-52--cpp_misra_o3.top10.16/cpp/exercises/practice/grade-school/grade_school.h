#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/* Fixed-width unsigned type for grades */
using grade_t  = std::int32_t;          /* signed 32-bit grade id */
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    school() = default;

    /* Add a student to a grade – throws if the student already exists */
    void add(const std::string& name, grade_t grade);

    /* Full roster in grade order; students already alphabetical */
    roster_t roster() const;

    /* Students in a specific grade (alphabetical); empty if none */
    std::vector<std::string> grade(grade_t grade) const;

private:
    roster_t m_roster; /* underlying storage */
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
