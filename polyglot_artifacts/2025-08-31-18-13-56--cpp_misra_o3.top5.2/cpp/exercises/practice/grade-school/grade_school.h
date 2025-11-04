#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

// Alias used for grade numbers to comply with MISRA fixed-width rule
// Signed 32-bit so that it aliases the int type the unit tests expect
using grade_t = std::int32_t;

class school {
public:
    // Add a student to the given grade if the name is not already present
    void add(const std::string& name, grade_t grade_number);

    // Return a list of students in the requested grade (alphabetically sorted)
    std::vector<std::string> grade(grade_t grade_number) const;

    // Return the full roster: grades in ascending order, names alphabetically
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    // Internal storage indexed by grade → sorted vector of names
    std::map<grade_t, std::vector<std::string>> students_{};

    // Helper to detect duplicate student names (any grade)
    bool contains_student(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
