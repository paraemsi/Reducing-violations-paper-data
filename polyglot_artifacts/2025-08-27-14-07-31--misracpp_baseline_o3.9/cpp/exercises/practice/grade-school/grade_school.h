#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

// A simple school roster that allows adding students to grades and retrieving
// the roster in the required order.
class school {
public:
    // Add a student's name to the given grade.
    // Throws std::domain_error if the student already exists anywhere in the roster.
    void add(const std::string& name, int grade);

    // Return the complete roster, ordered by grade then student name.
    std::map<int, std::vector<std::string>> roster() const;

    // Return the list of students in the requested grade, ordered alphabetically.
    std::vector<std::string> grade(int grade) const;

private:
    // Store each grade's students in a std::set to keep them unique and sorted.
    std::map<int, std::set<std::string>> records_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
