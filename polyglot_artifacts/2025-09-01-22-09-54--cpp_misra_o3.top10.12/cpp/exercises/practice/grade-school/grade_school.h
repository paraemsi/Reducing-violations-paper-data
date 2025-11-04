#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

namespace grade_school {

using grade_t = int;   // plain signed int required by test harness (must be 32-bit on target)
static_assert((sizeof(grade_t) == 4), "grade_t must be 32-bit signed int");

class school
{
public:
    //  Add a student to the requested grade.
    //  Returns false if the student is already present in any grade.
    bool add(const std::string& name, grade_t grade_level);

    //  Complete roster – grades in ascending order and names alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

    //  Students in a single grade – names alphabetically sorted.
    std::vector<std::string> grade(grade_t grade_level) const;

private:
    //  Internal storage keeps names unique and sorted.
    std::map<grade_t, std::set<std::string>> m_data;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
