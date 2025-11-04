#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

const std::vector<std::string> Garden::students = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

Garden::Garden(const std::string& diagram)
    : m_rows{}
{
    std::size_t start = 0U;
    std::size_t end = diagram.find('\n');
    while (end != std::string::npos) {
        m_rows.push_back(diagram.substr(start, (end - start)));
        start = end + 1U;
        end = diagram.find('\n', start);
    }
    m_rows.push_back(diagram.substr(start));
}

Garden::Plant char_to_plant(char c)
{
    switch (c) {
        case 'G': return Plant::grass;
        case 'C': return Plant::clover;
        case 'R': return Plant::radishes;
        case 'V': return Plant::violets;
        default: throw std::invalid_argument("Invalid plant code");
    }
}

std::vector<Garden::Plant> Garden::plants(const std::string& student) const
{
    auto it = std::find(students.begin(), students.end(), student);
    if (it == students.end()) {
        return {};
    }
    std::size_t idx = static_cast<std::size_t>(std::distance(students.begin(), it));
    std::vector<Plant> result;
    for (std::size_t row = 0U; row < 2U; ++row) {
        if (row >= m_rows.size()) {
            continue;
        }
        std::size_t pos = (idx * 2U);
        if ((pos + 1U) < m_rows[row].size()) {
            result.push_back(char_to_plant(m_rows[row][pos]));
            result.push_back(char_to_plant(m_rows[row][pos + 1U]));
        }
    }
    return result;
}

std::vector<Plant> plants(const std::string& diagram, const std::string& student)
{
    Garden garden(diagram);
    return garden.plants(student);
}

}  // namespace kindergarten_garden
