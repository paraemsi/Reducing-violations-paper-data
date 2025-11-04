#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

const std::vector<std::string> garden::children_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : rows_{}
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while (end != std::string::npos)
    {
        rows_.push_back(diagram.substr(start, (end - start)));
        start = (end + 1U);
        end = diagram.find('\n', start);
    }
    rows_.push_back(diagram.substr(start));
    if ((rows_.size() != 2U) || (rows_[0].size() != rows_[1].size()))
    {
        throw std::invalid_argument("Diagram must have exactly two rows of equal length");
    }
}

std::vector<Plant> garden::plants(const std::string& child) const
{
    child_index_t idx = child_index(child);
    std::vector<Plant> result;
    for (std::size_t row = 0U; row < 2U; ++row)
    {
        std::size_t base = (2U * static_cast<std::size_t>(idx));
        result.push_back(plant_from_char(rows_[row][base]));
        result.push_back(plant_from_char(rows_[row][(base + 1U)]));
    }
    return result;
}

Plant garden::plant_from_char(char c)
{
    switch (c)
    {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

child_index_t garden::child_index(const std::string& child)
{
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it == children_.end())
    {
        throw std::invalid_argument("Unknown child name");
    }
    return static_cast<child_index_t>(std::distance(children_.begin(), it));
}

std::vector<Plant> plants(const std::string& diagram, const std::string& child)
{
    garden g(diagram);
    return g.plants(child);
}

}  // namespace kindergarten_garden
