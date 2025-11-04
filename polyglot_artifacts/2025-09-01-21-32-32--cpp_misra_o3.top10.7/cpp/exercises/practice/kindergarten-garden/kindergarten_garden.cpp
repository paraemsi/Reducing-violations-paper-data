#include "kindergarten_garden.h"

#include <algorithm>
#include <string>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

std::vector<std::string_view> default_students()
{
    return { "Alice",  "Bob",  "Charlie", "David",
             "Eve",    "Fred", "Ginny",   "Harriet",
             "Ileana", "Joseph", "Kincaid", "Larry" };
}

Plants garden::char_to_plant(char diagram_char)
{
    if (diagram_char == 'G')
    {
        return Plants::grass;
    }
    else if (diagram_char == 'C')
    {
        return Plants::clover;
    }
    else if (diagram_char == 'R')
    {
        return Plants::radishes;
    }
    else if (diagram_char == 'V')
    {
        return Plants::violets;
    }
    else
    {
        throw std::invalid_argument("Invalid plant character in diagram");
    }
}

garden::garden(std::string_view diagram,
               std::vector<std::string_view> students)
{
    if (students.empty())
    {
        students = default_students();
    }

    std::vector<std::string> student_names{};
    student_names.reserve(students.size());
    for (std::string_view name_view : students)
    {
        student_names.emplace_back(name_view);
    }

    /* Keep the order provided by the caller – the default list is already
     * alphabetical, and custom lists must preserve their explicit ordering. */

    std::string diagram_str{ diagram };
    const std::size_t newline_pos{ diagram_str.find('\n') };

    std::string row_one{};
    std::string row_two{};

    if (newline_pos != std::string::npos)
    {
        row_one = diagram_str.substr(0U, newline_pos);
        row_two = diagram_str.substr(newline_pos + 1U);
    }
    else
    {
        row_one = diagram_str;
        row_two.clear();
    }

    const std::size_t expected_length{ 2U * student_names.size() };

    if ((row_one.length() < expected_length) || (row_two.length() < expected_length))
    {
        throw std::invalid_argument("Diagram does not contain enough cups");
    }

    for (std::size_t idx{ 0U }; idx < student_names.size(); ++idx)
    {
        const std::size_t pos{ static_cast<std::size_t>(2U * idx) };

        std::vector<Plants> assigned{};
        assigned.reserve(4U);

        assigned.emplace_back(char_to_plant(row_one[pos]));
        assigned.emplace_back(char_to_plant(row_one[pos + 1U]));
        assigned.emplace_back(char_to_plant(row_two[pos]));
        assigned.emplace_back(char_to_plant(row_two[pos + 1U]));

        (void)m_assignments.emplace(student_names[idx], assigned);
    }
}

std::vector<Plants> garden::plants(std::string_view student) const
{
    const auto it{ m_assignments.find(std::string(student)) };
    if (it != m_assignments.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}

KG_NODISCARD std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student)
{
    const garden g(diagram);
    const std::vector<Plants> vec{ g.plants(student) };

    std::array<Plants, 4U> result{};

    if ((vec.size() == 4U))
    {
        (void)std::copy(vec.begin(), vec.end(), result.begin());
    }

    return result;
}

} // namespace kindergarten_garden
