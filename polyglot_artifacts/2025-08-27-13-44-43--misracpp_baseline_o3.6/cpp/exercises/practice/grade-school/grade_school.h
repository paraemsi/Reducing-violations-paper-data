#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace grade_school {

class school {
public:
    // Add a student to a grade. If the student already exists in any grade
    // an exception is thrown to signal the logic error expected by tests.
    void add(const std::string& name, int grade);

    // Return alphabetically-sorted students in the requested grade.
    std::vector<std::string> grade(int grade) const;

    // Return the full roster. Grades are in ascending order and each grade’s
    // students are sorted alphabetically.
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Internal storage keeps students sorted automatically via std::set.
    std::map<int, std::set<std::string>> m_roster_;
    // Helper map to quickly detect attempts to re-add an existing student.
    std::unordered_map<std::string, int> m_student_index_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
