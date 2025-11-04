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
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while(end != std::string::npos)
    {
        rows_.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    rows_.push_back(diagram.substr(start));
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    student_index_t idx = student_index(student);
    std::vector<Plants> result;
    for(const auto& row : rows_)
    {
        // Each student gets two cups per row, starting at 2*idx
        result.push_back(plant_from_char(row.at((2U * idx))));
        result.push_back(plant_from_char(row.at(((2U * idx) + 1U))));
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
    return static_cast<student_index_t>(it - students_.begin());
}

Plants garden::plant_from_char(char c)
{
    switch(c)
    {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

std::vector<Plants> plants(const std::string& diagram, const std::string& student)
{
    kindergarten_garden::garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
