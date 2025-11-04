#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

/*
 * The `school` class stores the roster: a bidirectional mapping
 * between grades and students.  Each student may appear at most once
 * in the entire school.  Public member functions return *copies* of
 * internal containers so that callers cannot violate class invariants.
 */
class school {
public:
    using grade_type   = std::int32_t;
    using roster_type  = std::map<grade_type, std::vector<std::string>>;

    // Add a student to the given grade.
    // Returns `true` if the student was added, `false` if the student is
    // already present in the roster (in any grade).
    auto add(const std::string& name, grade_type grade) -> bool;

    // Return the list of students in a single grade (alphabetically-sorted).
    auto grade(grade_type grade) const -> std::vector<std::string>;

    // Return the full school roster, grades ascending, names alphabetical.
    [[nodiscard]] auto roster() const -> roster_type;

private:
    roster_type m_roster {};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
