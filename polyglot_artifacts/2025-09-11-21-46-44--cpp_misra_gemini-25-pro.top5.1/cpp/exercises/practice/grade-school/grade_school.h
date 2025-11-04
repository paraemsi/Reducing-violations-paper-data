#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    void add(const std::string& name, std::int32_t grade);
    std::vector<std::string> grade(std::int32_t grade_num) const;
    std::map<std::int32_t, std::vector<std::string>> roster() const;

private:
    std::map<std::int32_t, std::vector<std::string>> student_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
