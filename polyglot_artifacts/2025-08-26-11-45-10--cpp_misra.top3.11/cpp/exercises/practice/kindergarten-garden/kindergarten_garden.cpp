#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : rows_{}
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while(end != std::string::npos)
    {
        rows_.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    if(start < diagram.size())
    {
        rows_.push_back(diagram.substr(start));
    }
    if(rows_.size() != 2U)
    {
        throw std::invalid_argument("Diagram must have exactly two rows");
    }
    if((rows_[0].size() != rows_[1].size()) || ((rows_[0].size() % 2U) != 0U))
    {
        throw std::invalid_argument("Each row must have even number of cups and both rows must be equal length");
    }
}

std::vector<Plant> garden::plants(const std::string& student) const
{
    student_index_t idx = student_index(student);
    std::vector<Plant> result;
    for(std::size_t row = 0U; row < 2U; ++row)
    {
        std::size_t pos = static_cast<std::size_t>(idx) * 2U;
        result.push_back(char_to_plant(rows_[row][pos]));
        result.push_back(char_to_plant(rows_[row][pos + 1U]));
    }
    return result;
}

garden::student_index_t garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if(it == students_.end())
    {
        throw std::invalid_argument("Unknown student name");
    }
    return static_cast<student_index_t>(std::distance(students_.begin(), it));
}

Plant garden::char_to_plant(char c)
{
    switch(c)
    {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<Plant> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
