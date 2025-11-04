#include "grade_school.h"
#include <utility>

namespace grade_school {

bool school::add(const std::string& name, const grade_t grade_val)
{
    if ((all_students_.find(name) != all_students_.end())) {
        return false;
    } else {
        (void)all_students_.insert(name);
        (void)data_[grade_val].insert(name);
        return true;
    }
}

std::vector<std::string> school::grade(const grade_t grade_val) const
{
    const auto it = data_.find(grade_val);
    if ((it == data_.end())) {
        return std::vector<std::string>{};
    } else {
        std::vector<std::string> result{};
        result.reserve(it->second.size());
        for (const auto& s : it->second) {
            result.push_back(s);
        }
        return result;
    }
}

std::map<grade_t, std::vector<std::string>> school::roster() const
{
    std::map<grade_t, std::vector<std::string>> out{};
    for (const auto& kv : data_) {
        const grade_t g = kv.first;
        const std::set<std::string>& set_ref = kv.second;

        std::vector<std::string> vec{};
        vec.reserve(set_ref.size());
        for (const auto& s : set_ref) {
            vec.push_back(s);
        }
        (void)out.emplace(g, std::move(vec));
    }
    return out;
}

}  // namespace grade_school
