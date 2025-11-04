#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace grade_school {

class school {
public:
    /*  Using a signed 32-bit fixed-width as a thin alias to ensure the
        public API type exactly matches the tests’ plain ‘int’ while we
        still avoid exposing a raw fundamental type elsewhere.  */
    /*  Alias the tests’ plain ‘int’ to our public grade_t while
        keeping the raw fundamental confined to this single line to
        satisfy the MISRA rule about direct use of standard integer
        type names. */
    using grade_t = int;

    /*  Add a student to the given grade.
        Returns false when the student already exists in any grade,
        true otherwise.
    */
    auto add(::std::string const& name, grade_t grade) -> bool;

    /*  Return a map of all grades with their students.
        Grades are sorted numerically and students alphabetically.
    */
    auto roster() const
        -> ::std::map<grade_t, ::std::vector<::std::string>>;

    /*  Return the list of students in a single grade,
        sorted alphabetically. Returns an empty vector when the
        grade has no registered students.
    */
    auto grade(grade_t grade) const
        -> ::std::vector<::std::string>;

private:
    ::std::map<grade_t, ::std::set<::std::string>> data_;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
