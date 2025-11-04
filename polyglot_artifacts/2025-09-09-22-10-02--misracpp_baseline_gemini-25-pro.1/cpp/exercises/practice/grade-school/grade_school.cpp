#include "grade_school.h"
#include <algorithm>

namespace grade_school {

void school::add(const std::string& name, int grade) {
    auto it = name_to_grade_.find(name);

    if (it != name_to_grade_.end()) {
        int old_grade = it->second;
        if (old_grade == grade) {
            return;
        }

        auto grade_it = students_by_grade_.find(old_grade);
        auto& old_students = grade_it->second;
        auto student_it = std::lower_bound(old_students.begin(), old_students.end(), name);
        old_students.erase(student_it);
        if (old_students.empty()) {
            students_by_grade_.erase(grade_it);
        }
    }

    auto& new_students = students_by_grade_[grade];
    auto insert_pos = std::lower_bound(new_students.begin(), new_students.end(), name);
    new_students.insert(insert_pos, name);
    name_to_grade_[name] = grade;
}

const std::vector<std::string>& school::grade(int grade) const {
    auto it = students_by_grade_.find(grade);
    if (it != students_by_grade_.end()) {
        return it->second;
    }
    static const std::vector<std::string> empty_result;
    return empty_result;
}

const std::map<int, std::vector<std::string>>& school::roster() const {
    return students_by_grade_;
}

}  // namespace grade_school
