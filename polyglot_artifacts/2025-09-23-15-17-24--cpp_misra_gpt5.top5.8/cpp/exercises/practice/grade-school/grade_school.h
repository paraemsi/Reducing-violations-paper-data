#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

namespace grade_school {

class school {
public:
    using grade_type = std::int32_t;
    using roster_type = std::map<grade_type, std::vector<std::string>>;

    school() = default;
    ~school() = default;


    // Add a student to a grade; returns false if the student already exists in the roster
    bool add(std::string const& name, grade_type level);

    // Get a sorted list of students in the specified grade
    std::vector<std::string> grade(grade_type level) const;

    // Get the full roster: grades ascending, names within a grade sorted alphabetically
    roster_type roster() const;

private:
    roster_type roster_{};
    std::unordered_set<std::string> names_{};
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
