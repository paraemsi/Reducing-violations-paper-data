#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

const std::vector<std::string> garden::default_students{
    "Alice",  "Bob",    "Charlie", "David",  "Eve",   "Fred",
    "Ginny",  "Harriet","Ileana",  "Joseph", "Kincaid","Larry"};

garden::garden(std::string_view diagram) :
    garden(diagram, default_students)
{
}

garden::garden(std::string_view diagram,
               std::vector<std::string> const& students) :
    m_garden_map{}
{
    /* Split the diagram into exactly two rows. */
    std::string_view::size_type const newline_pos{diagram.find('\n')};

    if (newline_pos == std::string_view::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    std::string_view const row1{diagram.substr(0U, newline_pos)};
    std::string_view const row2{diagram.substr(newline_pos + 1U)};

    if (row1.size() != row2.size())
    {
        throw std::invalid_argument("Both rows must have the same length");
    }

    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    std::size_t const children_count{sorted_students.size()};

    if (row1.size() != (2U * children_count))
    {
        throw std::invalid_argument("Row length must equal twice the number of students");
    }

    for (std::size_t idx{0U}; idx < children_count; ++idx)
    {
        std::vector<plant> & target{m_garden_map[sorted_students[idx]]};

        /* Each child gets two cups per row, starting at column 2 * idx. */
        std::size_t const col{2U * idx};

        target.push_back(to_plant(row1[col]));
        target.push_back(to_plant(row1[col + 1U]));
        target.push_back(to_plant(row2[col]));
        target.push_back(to_plant(row2[col + 1U]));
    }
}

std::vector<plant> garden::plants(std::string const& student) const
{
    auto const it{m_garden_map.find(student)};

    if (it == m_garden_map.end())
    {
        throw std::out_of_range("Unknown student");
    }

    return it->second;
}

plant garden::to_plant(char token)
{
    switch (token)
    {
        case 'G':
            return plant::grass;
        case 'C':
            return plant::clover;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            throw std::invalid_argument("Invalid plant token");
    }
}

std::array<Plants, 4U> plants(std::string_view diagram, std::string const& student)
{
    garden const g{diagram};
    std::vector<plant> const vec{g.plants(student)};

    if (vec.size() != 4U)
    {
        throw std::logic_error("Expected exactly 4 plants per student");
    }

    std::array<Plants, 4U> arr{};
    for (std::size_t idx{0U}; idx < 4U; ++idx)
    {
        arr[idx] = vec[idx];
    }

    return arr;
}

}  // namespace kindergarten_garden
