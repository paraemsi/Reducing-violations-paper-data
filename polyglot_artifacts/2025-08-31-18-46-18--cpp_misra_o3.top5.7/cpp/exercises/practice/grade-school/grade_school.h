#ifndef GRADE_SCHOOL_H
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// Represents a school roster.
class school {
public:
    // Add a student to the specified grade.
    // Add a student to a grade.
    // If the student already exists in any grade, the call has no effect.
    void add(const std::string &name, std::int32_t grade_level);

    // Return the list of students in the given grade, sorted alphabetically.
    std::vector<std::string> grade(std::int32_t grade_level) const;

    // Return the complete roster: grades in ascending order and
    // students within each grade sorted alphabetically.
    std::map<std::int32_t, std::vector<std::string>> roster() const;

private:
    std::map<std::int32_t, std::set<std::string>> grades_ {}; // grade -> ordered set of names
    std::set<std::string> all_students_ {};                    // quick lookup to ensure uniqueness
};

} // namespace grade_school

#endif // GRADE_SCHOOL_H
