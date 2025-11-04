#include "grade_school.h"

#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_type grade)
{
    // Disallow adding the same student more than once anywhere in the roster.
    if ((all_students_.find(name) != all_students_.end())) {
        return false;
    }

    (void)all_students_.insert(name);
    (void)by_grade_[grade].insert(name);
    return true;
}

std::map<school::grade_type, std::vector<std::string>> school::roster() const
{
    std::map<grade_type, std::vector<std::string>> result{};

    for (const auto& kv : by_grade_) {
        const grade_type g = kv.first;
        const std::set<std::string>& names_set = kv.second;

        std::vector<std::string> names{};
        names.reserve(static_cast<std::vector<std::string>::size_type>(names_set.size()));

        for (const auto& s : names_set) {
            names.push_back(s);
        }

        (void)result.insert(std::make_pair(g, names));
    }

    return result;
}

std::vector<std::string> school::grade(grade_type grade_value) const
{
    std::vector<std::string> names{};

    const auto it = by_grade_.find(grade_value);
    if ((it != by_grade_.end())) {
        const std::set<std::string>& names_set = it->second;
        names.reserve(static_cast<std::vector<std::string>::size_type>(names_set.size()));

        for (const auto& s : names_set) {
            names.push_back(s);
        }
    }

    return names;
}

}  // namespace grade_school
