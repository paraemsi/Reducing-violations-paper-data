#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>

namespace grade_school {

// Represents a small-town school roster.
class school {
public:
    // Add a student to the given grade.
    // Returns true if the student was added successfully, or
    // false if the student is already enrolled in any grade.
    bool add(const std::string& name, int grade);

    // Retrieve a list of students in the requested grade,
    // sorted alphabetically.  Returns an empty list if the
    // grade has no enrolled students.
    std::vector<std::string> grade(int grade) const;

    // Return the full roster: a map keyed by grade (ascending)
    // with each value being a list of student names (alphabetical).
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps grades ordered numerically;
    // each grade keeps its students in alphabetical order.
    std::map<int, std::vector<std::string>> roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
