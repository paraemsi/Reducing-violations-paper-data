#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    using roster_t = std::map<int, std::vector<std::string>>;

    void add(const std::string& name, int g);
    std::vector<std::string> grade(int g) const;
    roster_t roster() const;

private:
    // Maintain unique, alphabetically sorted names per grade.
    std::map<int, std::set<std::string>> roster_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
