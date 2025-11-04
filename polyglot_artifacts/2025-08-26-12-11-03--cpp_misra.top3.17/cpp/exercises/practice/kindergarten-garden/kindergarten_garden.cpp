#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<plant> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

const std::vector<std::string> garden::students_ = {
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

plant garden::decode_plant(char c)
{
    switch (c)
    {
        case 'C': return plant::clover;
        case 'G': return plant::grass;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

garden::index_t garden::student_index(const std::string& student)
{
    auto it = std::find(students_.begin(), students_.end(), student);
    if (it == students_.end())
    {
        throw std::invalid_argument("Unknown student");
    }
    return static_cast<index_t>(it - students_.begin());
}

std::vector<plant> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<plant> result;
    for (const std::string& row : rows_)
    {
        result.push_back(decode_plant(row.at((2U * idx) + 0U)));
        result.push_back(decode_plant(row.at((2U * idx) + 1U)));
    }
    return result;
}

}  // namespace kindergarten_garden
