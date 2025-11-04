#include "kindergarten_garden.h"

#include <algorithm>
#include <sstream>
#include <iterator>
#include <array>

namespace kindergarten_garden {

garden::garden(const std::string& diagram, std::vector<std::string> students)
{
    if(students.empty())
    {
        m_students = {"Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                      "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
    }
    else
    {
        m_students = students;
        std::sort(m_students.begin(), m_students.end());
    }

    std::istringstream iss(diagram);

    /*  The input diagram provided by the tests may start with a leading
        newline.  In that case the first call to std::getline will return
        an empty string; perform an additional read to obtain the real
        first row. */
    (void)std::getline(iss, m_row1);
    if(m_row1.empty())
    {
        (void)std::getline(iss, m_row1);
    }
    (void)std::getline(iss, m_row2);
}

std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    auto it = std::find(m_students.begin(), m_students.end(), student);
    if(it == m_students.end())
    {
        return std::array<Plants, 4U>{};
    }

    std::size_t index = static_cast<std::size_t>(std::distance(m_students.begin(), it));
    std::size_t col_start = index * static_cast<std::size_t>(2U);

    std::array<Plants, 4U> result{
        char_to_plant(m_row1[col_start]),
        char_to_plant(m_row1[col_start + static_cast<std::size_t>(1U)]),
        char_to_plant(m_row2[col_start]),
        char_to_plant(m_row2[col_start + static_cast<std::size_t>(1U)])
    };

    return result;
}

Plants garden::char_to_plant(char symbol)
{
    switch(symbol)
    {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            /* Invalid symbol - returning grass as default */
            return Plants::grass;
    }
}

/* Free-function wrapper expected by the tests */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
