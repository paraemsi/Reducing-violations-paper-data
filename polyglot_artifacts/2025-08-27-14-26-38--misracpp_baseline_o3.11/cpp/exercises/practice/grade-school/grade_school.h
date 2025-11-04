#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>

namespace grade_school {

class school {
public:
    using roster_t = std::map<int, std::vector<std::string>>;

    // return the full roster, grades in ascending order, names alphabetically
    const roster_t& roster() const;

    // add a student to a grade – throws std::domain_error if the student already exists
    void add(const std::string& name, int grade);

    // return the list of students in a given grade, alphabetically sorted
    std::vector<std::string> grade(int grade) const;

private:
    roster_t roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
