#include "kindergarten_garden.h"
#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

const std::vector<std::string> kindergarten_garden::students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

kindergarten_garden::kindergarten_garden(const std::string& diagram)
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

kindergarten_garden::student_index_t kindergarten_garden::get_student_index(const std::string& student)
{
    auto it = std::find(students.begin(), students.end(), student);
    if (it == students.end())
    {
        throw std::invalid_argument("Unknown student name");
    }
    return static_cast<student_index_t>(it - students.begin());
}

std::vector<Plants> kindergarten_garden::plants(const std::string& student) const
{
    student_index_t idx = get_student_index(student);
    std::vector<Plants> result;
    for (const std::string& row : m_rows)
    {
        for (student_index_t i = 0U; i < 2U; ++i)
        {
            std::size_t pos = (2U * idx) + i;
            if (pos < row.size())
            {
                char c = row[pos];
                switch (c)
                {
                    case 'C':
                        result.push_back(Plants::clover);
                        break;
                    case 'G':
                        result.push_back(Plants::grass);
                        break;
                    case 'R':
                        result.push_back(Plants::radishes);
                        break;
                    case 'V':
                        result.push_back(Plants::violets);
                        break;
                    default:
                        // ignore unknown
                        break;
                }
            }
        }
    }
    return result;
}

// Static function for test compatibility
std::vector<Plants> kindergarten_garden::plants(const std::string& diagram, const std::string& student)
{
    kindergarten_garden garden(diagram);
    return garden.plants(student);
}

}  // namespace kindergarten_garden
