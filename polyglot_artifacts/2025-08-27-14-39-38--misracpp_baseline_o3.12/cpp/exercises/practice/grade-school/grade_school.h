#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
 public:
  // Add a student to a grade.  
  // Returns true on success, false if the student is already enrolled.
  bool add(const std::string& name, int grade);

  // Return a list of students in the specified grade, alphabetically sorted.
  std::vector<std::string> grade(int grade) const;

  // Return the full roster: map of grade -> vector of student names,
  // with grades in ascending order and student names alphabetically sorted.
  std::map<int, std::vector<std::string>> roster() const;

 private:
  // Internal storage: grade -> ordered set of student names
  std::map<int, std::set<std::string>> students_by_grade_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
