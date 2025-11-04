#include "grade_school.h"
#include <algorithm>
#include <set>

namespace grade_school {

void school::add(const std::string& name, std::int32_t grade) {
    // Check if the student is already in any grade
    // Since all_students tracks all added students, we can use it to check for duplicates
    if (all_students.find(name) != all_students.end()) {
        // If the student already exists, do nothing (indicate it's incorrect by not adding)
        return;
    }
    
    // Add to the all_students set
    all_students.insert(name);
    
    // Add to the appropriate grade and keep it sorted
    auto& students = students_by_grade[grade];
    // Insert in sorted order
    auto it = std::lower_bound(students.begin(), students.end(), name);
    students.insert(it, name);
}

std::vector<std::string> school::grade(std::int32_t grade_num) const {
    auto it = students_by_grade.find(grade_num);
    if (it != students_by_grade.end()) {
        // Return a copy of the vector which is always sorted
        return it->second;
    }
    // Return an empty vector if the grade doesn't exist
    return std::vector<std::string>();
}

std::map<std::int32_t, std::vector<std::string>> school::roster() const {
    // The map is ordered by key (grade number), and each vector is already sorted
    return students_by_grade;
}

}  // namespace grade_school
