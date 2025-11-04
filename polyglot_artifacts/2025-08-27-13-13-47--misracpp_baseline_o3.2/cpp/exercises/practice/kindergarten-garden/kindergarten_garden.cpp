#include "kindergarten_garden.h"
#include <array>

namespace kindergarten_garden {

const std::vector<std::string> default_students{
    "Alice",  "Bob",     "Charlie", "David",
    "Eve",    "Fred",    "Ginny",   "Harriet",
    "Ileana", "Joseph",  "Kincaid", "Larry"};

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument{"Unknown plant code"};
    }
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    auto newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos)
        throw std::invalid_argument{"Diagram must contain two rows separated by a newline"};

    m_row1 = diagram.substr(0, newline_pos);
    m_row2 = diagram.substr(newline_pos + 1);

    if (m_row1.size() != m_row2.size())
        throw std::invalid_argument{"Rows in diagram are not the same length"};

    m_students = students;
    std::sort(m_students.begin(), m_students.end());
}

std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = std::find(m_students.begin(), m_students.end(), student);
    if (it == m_students.end())
        throw std::invalid_argument{"Student not found"};

    std::size_t index = std::distance(m_students.begin(), it);
    std::size_t cup_pos = index * 2;

    if (cup_pos + 1 >= m_row1.size() || cup_pos + 1 >= m_row2.size())
        throw std::out_of_range{"Diagram does not contain cups for this student"};

    return {
        char_to_plant(m_row1[cup_pos]),
        char_to_plant(m_row1[cup_pos + 1]),
        char_to_plant(m_row2[cup_pos]),
        char_to_plant(m_row2[cup_pos + 1])
    };
}

/* Free-function wrapper demanded by the test suite. */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
