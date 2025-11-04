#include "grade_school.h"
#include <utility>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade)
{
    const std::pair<std::set<std::string>::iterator, bool> inserted_all = all_students_.insert(name);
    if ((inserted_all.second) == false)
    {
        return false;
    }

    by_grade_[grade].insert(name);
    return true;
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> result{};

    for (const std::pair<const grade_t, std::set<std::string>>& kv : by_grade_)
    {
        const grade_t g = kv.first;
        const std::set<std::string>& names = kv.second;

        std::vector<std::string> students{};
        students.reserve(names.size());
        for (const std::string& s : names)
        {
            students.push_back(s);
        }

        (void)result.emplace(g, std::move(students));
    }

    return result;
}

std::vector<std::string> school::grade(grade_t grade_level) const
{
    const auto it = by_grade_.find(grade_level);
    if ((it == by_grade_.end()))
    {
        return {};
    }
    const std::set<std::string>& names = it->second;

    std::vector<std::string> students{};
    students.reserve(names.size());
    for (const std::string& s : names)
    {
        students.push_back(s);
    }

    return students;
}

}  // namespace grade_school
