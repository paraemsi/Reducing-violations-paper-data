#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, int grade) {
  // Check for duplicate across all grades
  for (const auto& kv : students_by_grade_) {
    const auto& students = kv.second;
    if (students.count(name) != 0) {
      return false;  // already enrolled
    }
  }
  students_by_grade_[grade].insert(name);
  return true;
}

std::vector<std::string> school::grade(int grade) const {
  std::vector<std::string> result;
  auto it = students_by_grade_.find(grade);
  if (it != students_by_grade_.end()) {
    result.assign(it->second.begin(), it->second.end());
  }
  return result;
}

std::map<int, std::vector<std::string>> school::roster() const {
  std::map<int, std::vector<std::string>> result;
  for (const auto& kv : students_by_grade_) {
    int grade_level = kv.first;
    const auto& students = kv.second;
    result[grade_level].assign(students.begin(), students.end());
  }
  return result;
}

}  // namespace grade_school
