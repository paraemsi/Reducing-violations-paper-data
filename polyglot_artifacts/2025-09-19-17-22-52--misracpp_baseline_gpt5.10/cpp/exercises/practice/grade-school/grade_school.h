#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Returns true if the student was added; false if the student already exists in the roster.
    bool add(const std::string& name, int grade_number) noexcept;
    std::map<int, std::vector<std::string>> roster() const noexcept;
    std::vector<std::string> grade(int grade_number) const noexcept;

private:
    std::map<int, std::set<std::string>> students_by_grade_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
