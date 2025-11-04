#pragma once

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Fixed-width type to represent a grade number
using grade_t  = std::int32_t;

// Public roster type returned to callers
using roster_t = std::map<grade_t, std::vector<std::string>>;

class school {
public:
    // Add a student to a grade.
    // Add a student to a grade.
    // If the student already exists in any grade, the roster is left unchanged.
    void add(const std::string& name, grade_t grade_number);

    // Return the complete roster, sorted by grade and then by student name.
    roster_t roster() const;

    // Return the list of students in the specified grade (sorted).
    std::vector<std::string> grade(grade_t grade_number) const;

private:
    // Internal storage: set keeps names ordered and unique.
    std::map<grade_t, std::set<std::string>> m_roster_{};
};

}  // namespace grade_school
