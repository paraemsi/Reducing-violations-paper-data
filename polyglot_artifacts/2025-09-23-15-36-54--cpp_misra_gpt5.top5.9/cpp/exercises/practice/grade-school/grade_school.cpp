#include "grade_school.h"

#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t g)
{
    const auto it_student = m_students.find(name);
    if ((it_student != m_students.end())) {
        return false;
    } else {
        (void)m_students.insert(name);

        auto& vec = m_roster[g];
        vec.push_back(name);
        std::sort(vec.begin(), vec.end());

        return true;
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    auto result = m_roster;
    for (auto& kv : result) {
        auto& v = kv.second;
        std::sort(v.begin(), v.end());
    }
    return result;
}

std::vector<std::string> school::grade(grade_t g) const
{
    const auto it = m_roster.find(g);
    if ((it == m_roster.end())) {
        return std::vector<std::string>{};
    } else {
        auto vec = it->second;
        std::sort(vec.begin(), vec.end());
        return vec;
    }
}

}  // namespace grade_school
