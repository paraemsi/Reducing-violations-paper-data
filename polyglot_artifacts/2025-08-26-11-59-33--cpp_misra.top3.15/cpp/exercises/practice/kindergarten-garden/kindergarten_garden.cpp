#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

const std::vector<std::string> garden::s_students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram)
    : m_rows{}
{
    std::size_t pos = 0U;
    std::size_t next = 0U;
    while((next = diagram.find('\n', pos)) != std::string::npos)
    {
        m_rows.push_back(diagram.substr(pos, (next - pos)));
        pos = next + 1U;
    }
    if(pos < diagram.size())
    {
        m_rows.push_back(diagram.substr(pos));
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const
{
    index_t idx = student_index(student);
    std::array<Plants, 4> result{};
    std::size_t count = 0U;
    for(const std::string& row : m_rows)
    {
        // Each student gets two cups per row, starting at 2*idx
        index_t start = static_cast<index_t>(2U * idx);
        if((row.size() < (start + 2U)))
        {
            continue;
        }
        if(count < 4U) {
            result[count] = plant_enum(row[start]);
            ++count;
        }
        if(count < 4U) {
            result[count] = plant_enum(row[start + 1U]);
            ++count;
        }
    }
    return result;
}

Plants garden::plant_enum(char code)
{
    switch(code)
    {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: return Plants::grass; // fallback, should not happen
    }
}

garden::index_t garden::student_index(const std::string& student)
{
    auto it = std::find(s_students.begin(), s_students.end(), student);
    if(it == s_students.end())
    {
        throw std::out_of_range("Student not found");
    }
    return static_cast<index_t>(it - s_students.begin());
}

// Standalone function for test compatibility
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
