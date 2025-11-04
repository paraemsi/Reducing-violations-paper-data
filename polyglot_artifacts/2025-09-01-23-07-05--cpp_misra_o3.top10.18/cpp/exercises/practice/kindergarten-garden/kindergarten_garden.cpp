#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>   // for std::size_t
#include <iterator>  // for std::distance
#include <array>

namespace kindergarten_garden {

/* static */ const std::vector<std::string> garden::default_students {
    "Alice",  "Bob",    "Charlie", "David",
    "Eve",    "Fred",   "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : garden(diagram, garden::default_students)
{
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    /* Split the incoming diagram into its individual rows. */
    std::string current_row {};
    for(char ch : diagram) {
        if(ch == '\n') {
            m_rows.push_back(current_row);
            current_row.clear();
        } else {
            current_row.push_back(ch);
        }
    }
    if(!current_row.empty()) {
        m_rows.push_back(current_row);
    }

    /* Store and alphabetise the student list. */
    m_students = students;
    std::sort(m_students.begin(), m_students.end());
}

std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    const auto it =
        std::find(m_students.begin(), m_students.end(), student);

    /* Unknown student → four grass cups. */
    if(it == m_students.end()) {
        return std::array<Plants, 4U> {Plants::grass, Plants::grass,
                                       Plants::grass, Plants::grass};
    }

    const std::size_t index =
        static_cast<std::size_t>(std::distance(m_students.begin(), it));

    std::array<Plants, 4U> result {Plants::grass, Plants::grass,
                                   Plants::grass, Plants::grass};

    for(std::uint32_t row_idx {0U};
        row_idx < static_cast<std::uint32_t>(2U);
        ++row_idx)
    {
        if(row_idx >= m_rows.size()) {
            break;
        }
        const std::string& row = m_rows[row_idx];

        const std::size_t first =
            index * static_cast<std::size_t>(2U);
        const std::size_t second =
            first + static_cast<std::size_t>(1U);

        if(row.size() > second) {
            const std::size_t base =
                static_cast<std::size_t>(row_idx) *
                static_cast<std::size_t>(2U);
            result[base]       = char_to_plant(row[first]);
            result[base + static_cast<std::size_t>(1U)] =
                char_to_plant(row[second]);
        } else {
            result[row_idx * 2U]       = Plants::grass;
            result[(row_idx * 2U) + 1U] = Plants::grass;
        }
    }
    return result;
}

/* static */ Plants garden::char_to_plant(char code)
{
    switch(code) {
        case 'V':
            return Plants::violets;
        case 'R':
            return Plants::radishes;
        case 'C':
            return Plants::clover;
        case 'G':
            /* fallthrough */
        default:
            return Plants::grass;
    }
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g {diagram};
    return g.plants(student);
}

}  // namespace kindergarten_garden
