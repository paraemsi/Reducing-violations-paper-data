#include "grade_school.h"

#include <algorithm>
#include <tuple>  // required for structured bindings

namespace grade_school {

bool school::add(const std::string& name, int grade) {
  // Ensure the student does not already exist in any grade
  for (const auto& [g, students] : data_) {
    if (students.find(name) != students.end()) {
      return false;
    }
  }
  data_[grade].insert(name);  // std::set guarantees alphabetical order & uniqueness
  return true;
}

std::map<int, std::vector<std::string>> school::roster() const {
  std::map<int, std::vector<std::string>> result;
  for (const auto& [grade, students] : data_) {
    result[grade] = {students.begin(), students.end()};
  }
  return result;
}

std::vector<std::string> school::grade(int grade_level) const {
  auto it = data_.find(grade_level);
  if (it == data_.end()) {
    return {};
  }
  return {it->second.begin(), it->second.end()};
}

}  // namespace grade_school
