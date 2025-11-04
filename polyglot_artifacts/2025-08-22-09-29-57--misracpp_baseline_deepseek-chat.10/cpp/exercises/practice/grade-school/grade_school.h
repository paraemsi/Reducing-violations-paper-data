#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <set>

namespace grade_school {

class school {
private:
    std::map<int, std::vector<std::string>> roster_;
    std::map<std::string, int> student_grade_;
public:
    school() = default;
    
    void add(const std::string& name, int grade);
    std::vector<std::string> grade(int grade) const;
    std::map<int, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
