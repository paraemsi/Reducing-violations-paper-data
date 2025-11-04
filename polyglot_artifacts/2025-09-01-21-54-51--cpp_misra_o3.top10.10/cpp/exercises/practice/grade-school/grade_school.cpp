#include "grade_school.h"

namespace grade_school {

bool school::add(const std::string& name, grade_type grade)
{
    /* Check whether the student already exists in any grade. */
    for(const auto& grade_entry : m_roster)
    {
        const student_set& students{grade_entry.second};
        if(students.find(name) != students.end())
        {
            return false;   /* Duplicate found – do not add. */
        }
    }

    /* Insert the student into the desired grade; std::map will create the
       grade entry on-demand. */
    m_roster[grade].insert(name);
    return true;
}

school::roster_output school::roster() const
{
    roster_output result;
    for(const auto& grade_entry : m_roster)
    {
        const grade_type grd{grade_entry.first};
        result[grd] = student_list(grade_entry.second.begin(),
                                   grade_entry.second.end());
    }
    return result;
}

school::student_list school::grade(grade_type grade) const
{
    student_list result;
    const auto it{m_roster.find(grade)};
    if(it != m_roster.end())
    {
        result.insert(result.end(),
                      it->second.begin(),
                      it->second.end());
    }
    return result;
}

}  // namespace grade_school
