#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <vector>
#include <string>

namespace grade_school {

class school {
private:
    std::map<int, std::vector<std::string>> roster_;
public:
    // Add a student to a grade
    void add(const std::string& name, int grade);
    
    // Get all students in a grade, returns an empty vector if the grade doesn't exist
    std::vector<std::string> grade(int grade_num) const;
    
    // Get the complete school roster sorted by grade and then by name
    std::map<int, std::vector<std::string>> roster() const;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
