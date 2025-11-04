#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

namespace grade_school {

class school {
public:
    // Add a student to a grade.
    // Returns false if the student is already present (in any grade).
    bool add(const std::string& name, int grade);

    // Return an alphabetically-sorted list of students in the given grade.
    std::vector<std::string> grade(int grade) const;

    // Return the entire roster:
    // grades in ascending numeric order, students alphabetically within each grade.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Maintain students in sorted order and prevent duplicates.
    std::map<int, std::set<std::string>> grades_;          // grade → ordered set of names
    std::unordered_map<std::string, int> student_grade_;   // name  → grade
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
