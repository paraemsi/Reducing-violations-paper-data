#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;

class school {
public:
    // Add a student; returns false if the student already exists anywhere in the roster.
    bool add(const std::string& name, const grade_t grade_val);

    // Get a sorted list of students in a specific grade.
    std::vector<std::string> grade(const grade_t grade_val) const;

    // Get the full roster: grades sorted numerically and students alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> data_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
