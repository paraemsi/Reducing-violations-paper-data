#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

namespace {
    std::vector<std::string> default_students() {
        std::vector<std::string> s{
            "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
            "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
        };
        return s;
    }
}

Plants garden::map_char_to_plant(const char c) {
    if ((c == 'G')) {
        return Plants::grass;
    } else if ((c == 'C')) {
        return Plants::clover;
    } else if ((c == 'R')) {
        return Plants::radishes;
    } else if ((c == 'V')) {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(const std::string& diagram)
    : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : m_row1(), m_row2(), m_index_by_student() {
    const std::size_t pos = diagram.find('\n');
    if ((pos == std::string::npos)) {
        throw std::invalid_argument("Diagram must contain two rows separated by newline");
    } else {
        m_row1 = diagram.substr(static_cast<std::size_t>(0U), pos);
        m_row2 = diagram.substr(pos + static_cast<std::size_t>(1U));
    }

    if ((m_row1.size() != m_row2.size())) {
        throw std::invalid_argument("Both rows must be the same length");
    }

    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());
    for (std::size_t idx = static_cast<std::size_t>(0U); (idx < sorted_students.size()); ++idx) {
        const auto& name = sorted_students[idx];
        m_index_by_student.emplace(name, idx);
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const auto it = m_index_by_student.find(student);
    if ((it == m_index_by_student.end())) {
        throw std::out_of_range("Unknown student");
    }

    const std::size_t idx = it->second;
    const std::size_t base = (idx * static_cast<std::size_t>(2U));

    if (((m_row1.size() < (base + static_cast<std::size_t>(2U))) ||
         (m_row2.size() < (base + static_cast<std::size_t>(2U))))) {
        throw std::out_of_range("Not enough cups for student");
    }

    std::vector<Plants> result{};
    result.reserve(static_cast<std::size_t>(4U));
    result.push_back(map_char_to_plant(m_row1[base]));
    result.push_back(map_char_to_plant(m_row1[base + static_cast<std::size_t>(1U)]));
    result.push_back(map_char_to_plant(m_row2[base]));
    result.push_back(map_char_to_plant(m_row2[base + static_cast<std::size_t>(1U)]));
    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    const std::vector<Plants> v = g.plants(student);
    if ((v.size() != static_cast<std::size_t>(4U))) {
        throw std::logic_error("Unexpected number of plants");
    }
    std::array<Plants, 4> out{v[0], v[1], v[2], v[3]};
    return out;
}

}  // namespace kindergarten_garden
