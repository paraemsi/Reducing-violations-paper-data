#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
 public:
  // Add a student to the roster.  
  // Returns true if the student was successfully added,  
  // or false when the student already exists in the school.  
  bool add(const std::string& name, int grade);

  // Return a copy of the full roster, ordered by ascending grade
  // and alphabetically within each grade.
  std::map<int, std::vector<std::string>> roster() const;

  // Return all students in a specific grade, alphabetically sorted.
  std::vector<std::string> grade(int grade_level) const;

 private:
  // Internal storage: grade -> set of student names (kept sorted and unique)
  std::map<int, std::set<std::string>> data_;
};

}  // namespace grade_school

#endif  // GRADE_SCHOOL_H
