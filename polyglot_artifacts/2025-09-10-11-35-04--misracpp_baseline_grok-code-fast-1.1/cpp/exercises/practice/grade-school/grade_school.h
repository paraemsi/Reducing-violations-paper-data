#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace grade_school {

class school {
public:
    bool add(const std::string& name, int grade);
    std::vector<std::string> grade(int grade) const;
    std::map<int, std::vector<std::string>> roster() const;

private:
    std::map<int, std::set<std::string>> students_;
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
