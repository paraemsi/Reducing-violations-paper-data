#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

static Plant char_to_plant(char c)
{
    if(c == 'G')
    {
        return Plant::grass;
    }
    else if(c == 'C')
    {
        return Plant::clover;
    }
    else if(c == 'R')
    {
        return Plant::radishes;
    }
    else if(c == 'V')
    {
        return Plant::violets;
    }
    else
    {
        throw std::invalid_argument("Unknown plant code");
    }
}

Garden::Garden(std::string_view diagram)
    : Garden(diagram,
             std::vector<std::string>{ "Alice", "Bob", "Charlie", "David",
                                       "Eve", "Fred", "Ginny", "Harriet",
                                       "Ileana", "Joseph", "Kincaid", "Larry" })
{
    /* Delegating constructor handles everything. */
}

Garden::Garden(std::string_view diagram, const std::vector<std::string>& students)
{
    const auto pos_newline = diagram.find('\n');
    if(pos_newline == std::string_view::npos)
    {
        throw std::invalid_argument("Diagram must contain a newline separating the rows");
    }

    first_row_ = std::string(diagram.substr(0U, pos_newline));
    second_row_ = std::string(diagram.substr(pos_newline + 1U));

    students_.reserve(students.size());
    for(const std::string& name_ref : students)
    {
        students_.emplace_back(name_ref);
    }

    std::sort(students_.begin(), students_.end());

    populate_assignments();
}

void Garden::populate_assignments()
{
    const std::size_t child_count = students_.size();

    for(std::size_t idx = 0U; idx < child_count; ++idx)
    {
        std::vector<Plant> child_plants;
        child_plants.reserve(4U);

        const std::size_t col_start = (static_cast<std::size_t>(2U) * idx);

        if(((col_start + 1U) >= first_row_.size()) ||
           ((col_start + 1U) >= second_row_.size()))
        {
            throw std::out_of_range("Diagram does not have enough cups for each child");
        }

        child_plants.emplace_back(char_to_plant(first_row_.at(col_start)));
        child_plants.emplace_back(char_to_plant(first_row_.at(col_start + 1U)));
        child_plants.emplace_back(char_to_plant(second_row_.at(col_start)));
        child_plants.emplace_back(char_to_plant(second_row_.at(col_start + 1U)));

        assignments_.emplace(students_.at(idx), child_plants);
    }
}

std::vector<Plant> Garden::plants(std::string_view student) const
{
    const auto it = assignments_.find(std::string(student));
    if(it == assignments_.end())
    {
        return {};
    }
    return it->second;
}

PlantArray plants(std::string_view diagram, std::string_view student)
{
    Garden garden(diagram);
    const auto vec = garden.plants(student);

    if(vec.size() != 4U)
    {
        throw std::length_error("Each student must have exactly 4 plants");
    }

    PlantArray result{};
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        result[i] = vec.at(i);
    }
    return result;
}

}  // namespace kindergarten_garden
