#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

namespace grade_school {

/*  Type alias for grade identifiers.
 *  A 32-bit signed type is sufficient for typical school grade ranges
 *  and complies with the MISRA “no raw int” requirement. */
using grade_t = std::int32_t;

class school {
public:
    void add(const std::string& name, grade_t level);
    std::vector<std::string> grade(grade_t level) const; /* result may be discarded */
    std::map<grade_t, std::vector<std::string>> roster() const; /* result may be discarded */

private:
    /*  Internal storage:
     *  – std::map keeps grades in ascending order automatically.
     *  – std::set keeps students unique and alphabetically ordered. */
    std::map<grade_t, std::set<std::string>> m_data{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
