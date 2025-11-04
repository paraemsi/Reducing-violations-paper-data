#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

namespace {

Plants char_to_plant(char symbol)
{
    if(symbol == 'G')
    {
        return Plants::grass;
    }
    if(symbol == 'C')
    {
        return Plants::clover;
    }
    if(symbol == 'R')
    {
        return Plants::radishes;
    }
    if(symbol == 'V')
    {
        return Plants::violets;
    }

    throw std::invalid_argument("Invalid plant symbol");
}

std::vector<std::string> default_students()
{
    return { "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
             "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry" };
}

} // unnamed namespace

garden::garden(const std::string& diagram)
    : garden(diagram, default_students())
{
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
{
    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    std::string::size_type newline_pos = diagram.find('\n');
    if(newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows separated by newline");
    }

    const std::string first_row = diagram.substr(0U, newline_pos);
    const std::string second_row = diagram.substr(newline_pos + 1U);

    const std::uint32_t student_count = static_cast<std::uint32_t>(sorted_students.size());
    if((first_row.length() != (static_cast<std::uint32_t>(student_count) * 2U)) ||
       (second_row.length() != (static_cast<std::uint32_t>(student_count) * 2U)))
    {
        throw std::invalid_argument("Row length does not match student count");
    }

    for(std::uint32_t index = 0U; index < student_count; ++index)
    {
        const std::uint32_t pos = static_cast<std::uint32_t>(2U) * index;

        std::vector<Plants> assigned_plants;
        assigned_plants.reserve(4U);

        assigned_plants.push_back(char_to_plant(first_row[pos]));
        assigned_plants.push_back(char_to_plant(first_row[(pos + 1U)]));
        assigned_plants.push_back(char_to_plant(second_row[pos]));
        assigned_plants.push_back(char_to_plant(second_row[(pos + 1U)]));

        garden_map_.insert({ sorted_students[index], assigned_plants });
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it = garden_map_.find(student);
    if(it != garden_map_.end())
    {
        return it->second;
    }
    return {};
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    /* Determine how many children are represented in the supplied diagram
     * by dividing the length of the first row by two (two cups per child).
     * Restrict the default student list to that count so that the garden
     * constructor receives matching dimensions. */
    const std::string::size_type newline_pos = diagram.find('\n');
    if(newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    const std::string first_row = diagram.substr(0U, newline_pos);
    const std::uint32_t student_count = static_cast<std::uint32_t>(first_row.length()) / 2U;

    std::vector<std::string> students = default_students();
    if(student_count > static_cast<std::uint32_t>(students.size()))
    {
        throw std::invalid_argument("Diagram references more students than available in the default list");
    }
    students.resize(student_count);

    garden g(diagram, students);
    const std::vector<Plants> vec = g.plants(student);

    std::array<Plants, 4U> result{};

    if(vec.size() == 4U)
    {
        (void)std::copy_n(vec.begin(), 4U, result.begin());
    }
    return result;
}

}  // namespace kindergarten_garden
