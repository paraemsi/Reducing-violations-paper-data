#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H
#include <map>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade.
    // Returns true if the student was added, false if the student
    // is already present in any grade.
    bool add(const std::string& name, int grade);

    // Return the students in the requested grade, sorted alphabetically.
    std::vector<std::string> grade(int grade) const;

    // Return the full roster, sorted by grade then by student name.
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<int, std::vector<std::string>> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
