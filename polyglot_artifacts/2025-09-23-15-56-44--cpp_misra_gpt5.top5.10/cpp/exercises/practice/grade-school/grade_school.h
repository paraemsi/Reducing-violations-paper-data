#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace grade_school {

using grade_t = std::int32_t;
using roster_type = std::map<grade_t, std::vector<std::string>>;

class school {
 public:
  school() = default;

  bool add(const std::string& name, grade_t grade_level);
  std::vector<std::string> grade(grade_t grade_level) const;
  roster_type roster() const;

 private:
  roster_type roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
