#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> Garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Garden::Garden(const std::string& diagram)
    : rows_{}
{
    std::size_t pos = 0U;
    std::size_t next = 0U;
    while((next = diagram.find('\n', pos)) != std::string::npos)
    {
        rows_.push_back(diagram.substr(pos, (next - pos)));
        pos = (next + 1U);
    }
    if(pos < diagram.size())
    {
        rows_.push_back(diagram.substr(pos));
    }
}

Garden::index_t Garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if(it == students_.end())
    {
        throw std::invalid_argument("Unknown student name");
    }
    return static_cast<index_t>(it - students_.begin());
}

Garden::Plant Garden::char_to_plant(char c)
{
    switch(c)
    {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Invalid plant code");
    }
}

std::vector<Garden::Plant> Garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<Plant> result;
    for(const std::string& row : rows_)
    {
        // Each student gets two cups per row, starting at 2*idx
        if((row.size() >= (2U * (idx + 1U))))
        {
            result.push_back(char_to_plant(row[2U * idx]));
            result.push_back(char_to_plant(row[(2U * idx) + 1U]));
        }
    }
    return result;
}

// Free function for test compatibility
std::vector<Plant> plants(const std::string& diagram, const std::string& student)
{
    Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
