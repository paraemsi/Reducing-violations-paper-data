#include "kindergarten_garden.h"

#include <stdexcept>
#include <utility>
#include <array>

namespace kindergarten_garden {

plant garden::char_to_plant(char c)
{
    if (c == 'G')
    {
        return plant::grass;
    }
    else if (c == 'C')
    {
        return plant::clover;
    }
    else if (c == 'R')
    {
        return plant::radishes;
    }
    else if (c == 'V')
    {
        return plant::violets;
    }
    else
    {
        throw std::invalid_argument("Invalid plant encoding");
    }
}

garden::garden(std::string_view diagram, std::vector<std::string> students)
{
    const std::string_view::size_type newline_pos = diagram.find('\n');
    if (newline_pos == std::string_view::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    const std::string_view first_row = diagram.substr(0U, newline_pos);
    const std::string_view second_row = diagram.substr((newline_pos + 1U));

    if (first_row.size() != second_row.size())
    {
        throw std::invalid_argument("Rows must be the same length");
    }

    constexpr std::size_t cups_per_student { 2U };
    const std::size_t expected_students = first_row.size() / cups_per_student;

    if (expected_students != students.size())
    {
        throw std::invalid_argument("Student count does not match diagram width");
    }

    std::sort(students.begin(), students.end());

    for (std::size_t idx { 0U }; idx < students.size(); ++idx)
    {
        const std::size_t column_start = (idx * cups_per_student);
        std::vector<plant> p {};
        p.reserve(4U);

        p.push_back(char_to_plant(first_row[column_start]));
        p.push_back(char_to_plant(first_row[(column_start + 1U)]));
        p.push_back(char_to_plant(second_row[column_start]));
        p.push_back(char_to_plant(second_row[(column_start + 1U)]));

        (void)student_plants_.emplace(students[idx], std::move(p));
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it = student_plants_.find(student);
    if (it == student_plants_.end())
    {
        throw std::out_of_range("Student not found");
    }
    return it->second;
}

std::array<Plants, 4U> plants(std::string_view diagram,
                               std::string_view student,
                               std::vector<std::string> students)
{
    garden g(diagram, std::move(students));
    const std::vector<plant> vec = g.plants(std::string(student));
    if (vec.size() != 4U)
    {
        throw std::logic_error("Each student must have exactly four plants");
    }

    std::array<Plants, 4U> result {};
    for (std::size_t i { 0U }; i < 4U; ++i)
    {
        result[i] = vec[i];
    }
    return result;
}

}  // namespace kindergarten_garden
