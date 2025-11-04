#include "grade_school.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student is already in the roster using the set
    if (all_students.find(name) != all_students.end()) {
        // Student already exists, don't add again
        return;
    }
    
    // Add the student to the appropriate grade
    auto& grade_students = students_by_grade[grade];
    grade_students.push_back(name);
    // Sort the students alphabetically
    std::sort(grade_students.begin(), grade_students.end());
    
    // Add to the set of all students
    all_students.insert(name);
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    return students_by_grade;
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = students_by_grade.find(grade_num);
    if (it != students_by_grade.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

}  // namespace grade_school
