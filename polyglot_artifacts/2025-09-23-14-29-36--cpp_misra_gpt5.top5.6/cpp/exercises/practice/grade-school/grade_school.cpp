#include "grade_school.h"

#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level) {
    if ((m_all_names.find(name) != m_all_names.end())) {
        return false;
    }

    (void)m_all_names.insert(name);
    (void)m_roster[grade_level].insert(name);
    return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const {
    std::vector<std::string> list{};
    auto const it = m_roster.find(grade_level);
    if ((it != m_roster.end())) {
        list.reserve(it->second.size());
        for (auto const& n : it->second) {
            list.push_back(n);
        }
    } else {
        // no entries for this grade
    }
    return list;
}

roster_map_t school::roster() const {
    roster_map_t out{};
    for (auto const& pair : m_roster) {
        std::vector<std::string> v{};
        v.reserve(pair.second.size());
        for (auto const& n : pair.second) {
            v.push_back(n);
        }
        (void)out.emplace(static_cast<int>(pair.first), std::move(v));
    }
    return out;
}

}  // namespace grade_school
