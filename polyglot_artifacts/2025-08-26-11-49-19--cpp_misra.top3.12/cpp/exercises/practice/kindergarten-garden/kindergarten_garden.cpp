#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

const std::vector<std::string> garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : rows_{}
{
    std::size_t pos = 0U;
    std::size_t next = diagram.find('\n', pos);
    while(next != std::string::npos)
    {
        rows_.push_back(diagram.substr(pos, (next - pos)));
        pos = (next + 1U);
        next = diagram.find('\n', pos);
    }
    if(pos < diagram.size())
    {
        rows_.push_back(diagram.substr(pos));
    }
    if(rows_.size() != 2U)
    {
        throw std::invalid_argument("Diagram must have exactly two rows");
    }
    if((rows_[0].size() != rows_[1].size()) || (rows_[0].size() != (students_.size() * 2U)))
    {
        throw std::invalid_argument("Each row must have 2 cups per student");
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<Plants> result;
    result.reserve(4U);
    for(index_t row = 0U; row < 2U; ++row)
    {
        for(index_t cup = 0U; cup < 2U; ++cup)
        {
            result.push_back(char_to_plant(rows_[row][(2U * idx) + cup]));
        }
    }
    return result;
}

garden::index_t garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if(it == students_.end())
    {
        throw std::invalid_argument("Unknown student: " + student);
    }
    return static_cast<index_t>(it - students_.begin());
}

Plants garden::char_to_plant(char c)
{
    switch(c)
    {
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
