#include "grade_school.h"
#include <utility>      // for std::move

namespace grade_school {

auto school::add(::std::string const& name, grade_t grade) -> bool
{
    /*  Reject duplicate student names (a student can appear only once
        in the entire school, irrespective of grade).
    */
    for (auto const& grade_pair : data_) {
        if (grade_pair.second.find(name) != grade_pair.second.end()) {
            return false;
        }
    }

    /*  Insert the student into the requested grade. The set keeps the
        names sorted automatically and ensures uniqueness within the
        grade. The previous duplicate check guarantees that the overall
        roster remains unique.
    */
    auto& students = data_[grade];
    (void)students.insert(name);

    return true;
}

auto school::roster() const
    -> ::std::map<grade_t, ::std::vector<::std::string>>
{
    ::std::map<grade_t, ::std::vector<::std::string>> result {};

    for (auto const& grade_pair : data_) {
        ::std::vector<::std::string> names { grade_pair.second.begin(),
                                             grade_pair.second.end() };
        result.emplace(grade_pair.first, ::std::move(names));
    }

    return result;
}

auto school::grade(grade_t grade_level) const
    -> ::std::vector<::std::string>
{
    auto const iter = data_.find(grade_level);

    if (iter == data_.end()) {
        return {};
    } else {
        return { iter->second.begin(), iter->second.end() };
    }
}

}  // namespace grade_school
