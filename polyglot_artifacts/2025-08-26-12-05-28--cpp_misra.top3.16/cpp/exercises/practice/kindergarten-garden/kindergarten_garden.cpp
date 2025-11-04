#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
{
    std::string::size_type pos = 0U;
    std::string::size_type next = 0U;
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

garden::index_t garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if(it == students_.end())
    {
        throw std::invalid_argument("Unknown student name");
    }
    return static_cast<index_t>(it - students_.begin());
}

garden::Plant garden::char_to_plant(char c)
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

std::vector<garden::Plant> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<Plant> result;
    for(const std::string& row : rows_)
    {
        if((row.size() < ((static_cast<std::size_t>(idx) * 2U) + 2U)))
        {
            throw std::out_of_range("Diagram row too short for student index");
        }
        result.push_back(char_to_plant(row.at((static_cast<std::size_t>(idx) * 2U) + 0U)));
        result.push_back(char_to_plant(row.at((static_cast<std::size_t>(idx) * 2U) + 1U)));
    }
    return result;
}

std::vector<garden::Plant> kindergarten_garden::plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
