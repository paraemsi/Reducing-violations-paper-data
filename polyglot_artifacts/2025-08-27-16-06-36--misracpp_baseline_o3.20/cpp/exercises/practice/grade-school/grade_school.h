#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

class school {
 public:
    using roster_t = std::map<int, std::vector<std::string>>;

    // Adds a student to the given grade.
    // Returns true if the student was added, or false if the student
    // already exists in the roster.
    bool add(const std::string& name, int grade);

    // Returns the full school roster, sorted by grade, then by name.
    const roster_t& roster() const;

    // Returns a list of students in the given grade, sorted by name.
    const std::vector<std::string>& grade(int grade) const;

 private:
    roster_t roster_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
