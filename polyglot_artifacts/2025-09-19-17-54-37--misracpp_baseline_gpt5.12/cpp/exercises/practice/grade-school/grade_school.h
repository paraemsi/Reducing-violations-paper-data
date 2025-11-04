#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_t = int;

    // Add a student's name to the given grade.
    // Returns true if added; false if the student is already enrolled anywhere.
    bool add(const std::string& name, grade_t g);

    // Get an alphabetically sorted list of students in the given grade.
    std::vector<std::string> grade(grade_t g) const;

    // Get the full roster: grades ascending; students within each grade alphabetically.
    std::map<grade_t, std::vector<std::string>> roster() const;

private:
    std::map<grade_t, std::set<std::string>> roster_sets_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
