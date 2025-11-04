#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    school() = default;

    // Add a student's name to a grade (duplicates across the whole roster are ignored)
    void add(const std::string& name, int grade);

    // Return a copy of the full roster: grades ascending, names alphabetically
    std::map<int, std::vector<std::string>> roster() const;

    // Return a copy of the students in a specific grade (alphabetically sorted)
    std::vector<std::string> grade(int grade) const;

private:
    bool contains_student(const std::string& name) const;

    std::map<int, std::vector<std::string>> roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
