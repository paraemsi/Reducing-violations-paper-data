#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <map>
#include <vector>

namespace grade_school {

using roster_t = std::map<int, std::vector<std::string>>;

class school {
public:
    // Add a student to a grade. If the student already exists in the same
    // grade, the request is ignored. If the student exists in a different
    // grade, they are moved to the new grade.
    void add(const std::string &name, int grade);

    // Full roster, ordered by grade (ascending) then student name (alpha).
    const roster_t& roster() const;

    // All students in a single grade, ordered alphabetically.
    std::vector<std::string> grade(int grade) const;

private:
    roster_t m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
