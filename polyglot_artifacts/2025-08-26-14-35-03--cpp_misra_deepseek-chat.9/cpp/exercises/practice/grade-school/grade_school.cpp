#include "grade_school.h"
#include <algorithm>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student already exists in the entire school
    // If they do, don't add them again
    if (all_students.find(name) != all_students.end()) {
        return;
    }
    
    // Add to the appropriate grade
    auto& grade_list = students_by_grade[grade];
    grade_list.push_back(name);
    // Sort the list alphabetically
    std::sort(grade_list.begin(), grade_list.end());
    // Add to all students set
    all_students.insert(name);
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    // The map is already ordered by grade number, and each vector is sorted alphabetically
    return students_by_grade;
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = students_by_grade.find(grade_num);
    if (it != students_by_grade.end()) {
        return it->second;
    }
    return {};
}

}  // namespace grade_school
