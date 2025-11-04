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
    while (end != std::string::npos)
    {
        rows_.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    rows_.push_back(diagram.substr(start));
}

std::vector<plant> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<plant> result;
    for (const std::string& row : rows_)
    {
        // Each student gets 2 cups per row, starting at 2*idx
        index_t base = static_cast<index_t>(2U * idx);
        if ((base + 1U) >= row.size())
        {
            continue;
        }
        result.push_back(decode_plant(row[base]));
        result.push_back(decode_plant(row[base + 1U]));
    }
    return result;
}

plant garden::decode_plant(char code)
{
    switch (code)
    {
        case 'C': return plant::clover;
        case 'G': return plant::grass;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default: throw std::invalid_argument("Unknown plant code");
    }
}

index_t garden::student_index(const std::string& student)
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
    kindergarten_garden::garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
