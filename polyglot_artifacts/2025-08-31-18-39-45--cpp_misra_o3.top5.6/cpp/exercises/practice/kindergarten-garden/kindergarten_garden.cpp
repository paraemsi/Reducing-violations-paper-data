#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>

namespace kindergarten_garden {

/* Default list of students in alphabetical order. */
const std::array<std::string, 12U> garden::default_students = {
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

/* Convert a diagram code letter to the matching plant. */
static Plants char_to_plant(char code)
{
    if (code == 'G') { return Plants::grass; }
    if (code == 'C') { return Plants::clover; }
    if (code == 'R') { return Plants::radishes; }
    if (code == 'V') { return Plants::violets; }

    throw std::invalid_argument("Invalid plant code in diagram");
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
    : m_row0()
    , m_row1()
    , m_students(students)
{
    const std::string::size_type newline_pos = diagram.find('\n');

    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain exactly two rows");
    }

    m_row0 = diagram.substr(0U, newline_pos);
    m_row1 = diagram.substr((newline_pos + 1U));

    if ((m_row0.length() != m_row1.length()) ||
        ((m_row0.length() % 2U) != 0U)) {
        throw std::invalid_argument("Rows must be of equal even length");
    }

    const std::size_t num_students = m_row0.length() / 2U;

    if (students.empty()) {
        m_students.assign(default_students.begin(),
                          default_students.begin() + num_students);
    } else {
        if (students.size() > num_students) {
            throw std::invalid_argument("More students than available cup pairs");
        }
        /* m_students already initialised from the provided list. */
    }

    std::sort(m_students.begin(), m_students.end());
}

std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    const auto it = std::find(m_students.begin(), m_students.end(), student);

    if (it == m_students.end()) {
        throw std::out_of_range("Student not found");
    }

    const std::size_t index = static_cast<std::size_t>(std::distance(m_students.begin(), it));
    const std::size_t start = index * 2U;

    std::array<Plants, 4U> result{
        char_to_plant(m_row0[start]),
        char_to_plant(m_row0[(start + 1U)]),
        char_to_plant(m_row1[start]),
        char_to_plant(m_row1[(start + 1U)])
    };

    return result;
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students)
{
    const garden g(diagram, students);
    return g.plants(student);
}

}  // namespace kindergarten_garden
