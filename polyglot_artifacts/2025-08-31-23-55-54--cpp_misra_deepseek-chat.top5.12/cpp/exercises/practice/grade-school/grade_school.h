#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace grade_school {

class school {
private:
    std::map<std::uint32_t, std::vector<std::string>> roster_;
    std::unordered_set<std::string> student_set_;
public:
    school() = default;
    void add(const std::string& name, std::uint32_t grade);
    std::map<std::uint32_t, std::vector<std::string>> roster() const;
    std::vector<std::string> grade(std::uint32_t grade_number) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
