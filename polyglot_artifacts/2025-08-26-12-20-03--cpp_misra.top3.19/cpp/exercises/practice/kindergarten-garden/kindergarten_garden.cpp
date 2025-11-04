#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

const std::vector<std::string> Garden::students_ = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Garden::Garden(const std::string& diagram)
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
    if (start < diagram.size())
    {
        rows_.push_back(diagram.substr(start));
    }
    if (rows_.size() != 2U)
    {
        throw std::invalid_argument("Diagram must have exactly two rows");
    }
}

std::vector<Plant> Garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<Plant> result;
    for (index_t row = 0U; row < 2U; ++row)
    {
        index_t pos = static_cast<index_t>(2U * idx);
        result.push_back(char_to_plant(rows_.at(row).at(pos)));
        result.push_back(char_to_plant(rows_.at(row).at(pos + 1U)));
    }
    return result;
}

Plant Garden::char_to_plant(char c)
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

index_t Garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end())
    {
        throw std::invalid_argument("Unknown student");
    }
    return static_cast<index_t>(std::distance(students_.begin(), it));
}

std::vector<kindergarten_garden::Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student)
{
    Garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
