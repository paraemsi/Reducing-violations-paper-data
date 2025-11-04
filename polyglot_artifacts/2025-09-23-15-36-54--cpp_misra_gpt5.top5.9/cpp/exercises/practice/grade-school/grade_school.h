#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = int;

class school {
public:
    school() = default;

    bool add(const std::string& name, grade_t g);
    std::map<grade_t, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(grade_t g) const;

private:
    std::map<grade_t, std::vector<std::string>> m_roster{};
    std::set<std::string> m_students{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
