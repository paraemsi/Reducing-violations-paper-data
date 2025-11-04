#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using Grade = std::int32_t;
using Name = std::string;
using roster_t = std::map<Grade, std::vector<Name>>;

class school {
public:
    school() = default;

    bool add(const Name& name, Grade level);
    std::vector<Name> grade(Grade level) const;
    roster_t roster() const;

private:
    roster_t roster_;
    std::map<Name, Grade> directory_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
