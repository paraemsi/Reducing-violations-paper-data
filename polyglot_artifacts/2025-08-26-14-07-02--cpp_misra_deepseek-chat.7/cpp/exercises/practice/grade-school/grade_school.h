#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
public:
    bool add(const std::string& name, int grade);
    std::map<int, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(int grade) const;
    
private:
    std::map<std::uint32_t, std::vector<std::string>> students_by_grade;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
