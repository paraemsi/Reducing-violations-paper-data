#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

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
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    rows_.push_back(diagram.substr(start));
}

std::vector<Plants> garden::plants(const std::string& child_name) const
{
    child_index_t idx = child_index(child_name);
    std::vector<Plants> result;
    for (const std::string& row : rows_)
    {
        std::size_t pos = static_cast<std::size_t>(idx) * 2U;
        if ((pos + 1U) < row.size())
        {
            result.push_back(decode_plant(row[pos]));
            result.push_back(decode_plant(row[pos + 1U]));
        }
    }
    return result;
}

garden::child_index_t garden::child_index(const std::string& child_name)
{
    auto it = std::find(children_.begin(), children_.end(), child_name);
    if (it == children_.end())
    {
        throw std::invalid_argument("Unknown child name");
    }
    return static_cast<child_index_t>(it - children_.begin());
}

Plants garden::decode_plant(char code)
{
    switch (code)
    {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Invalid plant code");
    }
}

std::vector<Plants> plants(const std::string& diagram, const std::string& child_name)
{
    garden g(diagram);
    return g.plants(child_name);
}

}  // namespace kindergarten_garden
