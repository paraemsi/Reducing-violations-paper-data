#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>

namespace kindergarten_garden {

namespace {
constexpr std::uint8_t cups_per_child{2U};
[[maybe_unused]] constexpr std::uint8_t rows_in_diagram{2U};  // kept for clarity, unused but informative
}  // namespace

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : m_students{students.empty() ? default_students() : students}
{
    /* Split the diagram into its two expected rows */
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("diagram must contain exactly two rows");
    }

    const std::string row1{diagram.substr(0U, newline_pos)};
    const std::string row2{diagram.substr(newline_pos + 1U)};

    if (row1.length() != row2.length())
    {
        throw std::invalid_argument("diagram rows must be of equal length");
    }

    if ((row1.length() % cups_per_child) != 0U)
    {
        throw std::invalid_argument("row length must be divisible by 2");
    }

    /* Ensure there are enough cups for every student */
    const std::size_t expected_length{m_students.size() * static_cast<std::size_t>(cups_per_child)};
    if (row1.length() < expected_length)
    {
        throw std::invalid_argument("not enough cups for students");
    }

    /* Students are ordered alphabetically */
    std::sort(m_students.begin(), m_students.end());

    m_assignments.resize(m_students.size(), std::vector<Plants>{});

    for (std::size_t child_index{0U}; child_index < m_students.size(); ++child_index)
    {
        const std::size_t column{child_index * static_cast<std::size_t>(cups_per_child)};

        const char cup1_row1{row1.at(column)};
        const char cup2_row1{row1.at(column + 1U)};
        const char cup1_row2{row2.at(column)};
        const char cup2_row2{row2.at(column + 1U)};

        m_assignments.at(child_index).push_back(char_to_plant(cup1_row1));
        m_assignments.at(child_index).push_back(char_to_plant(cup2_row1));
        m_assignments.at(child_index).push_back(char_to_plant(cup1_row2));
        m_assignments.at(child_index).push_back(char_to_plant(cup2_row2));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it{std::find(m_students.begin(), m_students.end(), student)};
    if (it == m_students.end())
    {
        throw std::invalid_argument("student not found");
    }

    const std::size_t index{
        static_cast<std::size_t>(std::distance(m_students.begin(), it))};

    return m_assignments.at(index);
}

Plants garden::char_to_plant(char code)
{
    switch (code)
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
            throw std::invalid_argument("invalid plant code");
    }
}

std::vector<std::string> garden::default_students()
{
    return {"Alice",   "Bob",  "Charlie", "David",
            "Eve",     "Fred", "Ginny",   "Harriet",
            "Ileana",  "Joseph", "Kincaid", "Larry"};
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g{diagram};

    const std::vector<Plants> vec{g.plants(student)};
    if (vec.size() != 4U)
    {
        throw std::logic_error("each student must have exactly 4 plants");
    }

    std::array<Plants, 4U> arr{};
    for (std::size_t i{0U}; i < 4U; ++i)
    {
        arr.at(i) = vec.at(i);
    }

    return arr;
}

}  // namespace kindergarten_garden
