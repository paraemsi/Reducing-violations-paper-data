#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    // Add a student to a grade
    void add(const std::string& student_name, int grade);
    
    // Get all students in a specific grade, sorted alphabetically
    std::vector<std::string> grade(int grade_number) const;
    
    // Get all students in all grades
    // Returns a map where keys are grades (sorted) and values are sorted student names
    std::map<int, std::vector<std::string>> roster() const;

private:
    // Store students by grade, using set for automatic alphabetical sorting
    std::map<int, std::set<std::string>> roster_;
    
    // Track all students to prevent duplicates across grades
    std::set<std::string> all_students_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
