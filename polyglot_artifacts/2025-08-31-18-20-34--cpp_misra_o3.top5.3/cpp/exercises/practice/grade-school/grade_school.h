#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace grade_school {

class school {
public:
    using grade_type = std::int32_t;

    school() = default;

    /*  Add a student to the requested grade.
        Returns true on success, false if the student is already present. */
    bool add(const std::string& name, grade_type grade);

    /*  Complete, sorted roster (grades ascending, names alphabetical). */
    std::map<grade_type, std::vector<std::string>> roster() const;

    /*  Students in the requested grade, alphabetically sorted. */
    std::vector<std::string> grade(grade_type grade_number) const;

private:
    std::map<grade_type, std::vector<std::string>> m_roster;
};

}  // namespace grade_school

#endif // GRADE_SCHOOL_H
