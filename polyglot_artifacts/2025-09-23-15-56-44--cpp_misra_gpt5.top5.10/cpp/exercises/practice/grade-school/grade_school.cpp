#include "grade_school.h"
#include <algorithm>

namespace grade_school {

bool school::add(const std::string& name, grade_t grade_level) {
  // Reject if the student is already in any grade
  for (const auto& entry : roster_) {
    const std::vector<std::string>& students = entry.second;
    if ((std::find(students.begin(), students.end(), name) != students.end())) {
      return false;
    }
  }

  std::vector<std::string>& students_in_grade = roster_[grade_level];
  students_in_grade.push_back(name);
  std::sort(students_in_grade.begin(), students_in_grade.end());
  return true;
}

std::vector<std::string> school::grade(grade_t grade_level) const {
  auto it = roster_.find(grade_level);
  if ((it == roster_.end())) {
    return {};
  } else {
    return it->second;
  }
}

roster_type school::roster() const {
  return roster_;
}

}  // namespace grade_school
