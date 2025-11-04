#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace grade_school {

class school {
public:
    using grade_t  = std::int32_t;
    using roster_t = std::map<grade_t, std::vector<std::string>>;

    void add(const std::string& name, grade_t grade);
    std::vector<std::string> grade(grade_t grade) const;
    roster_t roster() const;

private:
    roster_t roster_{};

    bool student_exists(const std::string& name) const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
