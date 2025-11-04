#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

const std::vector<std::string> kindergarten_garden::students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

kindergarten_garden::kindergarten_garden(const std::string& diagram)
    : m_rows()
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while(end != std::string::npos)
    {
        m_rows.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    m_rows.push_back(diagram.substr(start));
}

std::vector<Plants> kindergarten_garden::plants(const std::string& student) const
{
    student_index_t idx = get_student_index(student);
    std::vector<Plants> result;
    for(const std::string& row : m_rows)
    {
        std::size_t pos = static_cast<std::size_t>(idx) * 2U;
        if((pos + 1U) < row.size())
        {
            result.push_back(char_to_plant(row[pos]));
            result.push_back(char_to_plant(row[(pos + 1U)]));
        }
    }
    return result;
}

// Static interface for test compatibility
std::vector<Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student)
{
    kindergarten_garden kg(diagram);
    return kg.plants(student);
}

kindergarten_garden::student_index_t kindergarten_garden::get_student_index(const std::string& student)
{
    auto it = std::find(students.begin(), students.end(), student);
    if(it == students.end())
    {
        throw std::invalid_argument("Unknown student name");
    }
    return static_cast<student_index_t>(it - students.begin());
}

Plants kindergarten_garden::char_to_plant(char c)
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

}  // namespace kindergarten_garden
