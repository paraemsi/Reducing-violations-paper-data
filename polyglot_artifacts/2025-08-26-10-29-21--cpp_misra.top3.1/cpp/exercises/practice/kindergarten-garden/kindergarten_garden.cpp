#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

const std::vector<std::string> garden::m_students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : m_rows{}
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while (end != std::string::npos)
    {
        m_rows.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    m_rows.push_back(diagram.substr(start));
}

std::vector<plant> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::vector<plant> result;
    for (const std::string& row : m_rows)
    {
        index_t pos = static_cast<index_t>(2U * idx);
        if ((pos + 1U) < static_cast<index_t>(row.size()))
        {
            result.push_back(decode_plant(row.at(pos)));
            result.push_back(decode_plant(row.at(pos + 1U)));
        }
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
    auto it = std::find(m_students.begin(), m_students.end(), student);
    if (it == m_students.end())
    {
        throw std::invalid_argument("Unknown student");
    }
    return static_cast<index_t>(std::distance(m_students.begin(), it));
}

std::vector<plant> garden::plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
