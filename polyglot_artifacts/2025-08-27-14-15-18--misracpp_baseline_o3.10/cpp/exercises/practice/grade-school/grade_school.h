#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    using roster_t = std::map<int, std::vector<std::string>>;

    // Add a student to a grade. If the student already exists anywhere, ignore.
    void add(const std::string& name, int grade);

    // Return the students in the specified grade, alphabetically sorted.
    std::vector<std::string> grade(int grade) const;

    // Return the full school roster: grades sorted 1..N, students alphabetically.
    roster_t roster() const;

private:
    // Internal storage keeps students sorted and guarantees uniqueness.
    std::map<int, std::set<std::string>> students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
