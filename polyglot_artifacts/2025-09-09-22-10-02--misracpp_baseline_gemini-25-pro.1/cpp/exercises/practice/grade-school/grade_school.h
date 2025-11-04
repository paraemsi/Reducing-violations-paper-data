#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>

namespace grade_school {
class school {
   public:
    void add(const std::string& name, int grade);
    const std::vector<std::string>& grade(int grade) const;
    const std::map<int, std::vector<std::string>>& roster() const;

   private:
    std::map<int, std::vector<std::string>> students_by_grade_;
    std::map<std::string, int> name_to_grade_;
};
}  // namespace grade_school

#endif // GRADE_SCHOOL_H
