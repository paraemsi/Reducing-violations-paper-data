#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <array>

namespace kindergarten_garden {

namespace {

/*  The order of students, sorted alphabetically as required by the
    problem statement. */
const std::vector<std::string> k_students{
    "Alice",  "Bob",  "Charlie", "David",
    "Eve",    "Fred", "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"
};

/* Convert a diagram character to the corresponding plant enum. */
plant char_to_plant(char ch) {
    switch (ch) {
        case 'C':
            return plant::clover;
        case 'G':
            return plant::grass;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            throw std::invalid_argument("Unknown plant code in diagram.");
    }
}

}  // unnamed namespace

garden::garden(const std::string& diagram) : m_students{k_students} {
    std::string current_line{};
    for (const char ch : diagram) {
        if (ch == '\n') {
            if (!current_line.empty()) {
                m_rows.push_back(current_line);
                current_line.clear();
            }
        } else {
            current_line.push_back(ch);
        }
    }
    if (!current_line.empty()) {
        m_rows.push_back(current_line);
    }

    /* The diagram must contain exactly two rows. */
    if (m_rows.size() != static_cast<std::size_t>(2U)) {
        throw std::invalid_argument("Diagram must contain exactly two rows.");
    }
}

std::array<kindergarten_garden::Plants, 4U> kindergarten_garden::plants(
    const std::string& diagram,
    const std::string& student) {
    const kindergarten_garden::garden g(diagram);
    const std::vector<kindergarten_garden::plant> vec{g.plants(student)};

    if (vec.size() != static_cast<std::size_t>(4U)) {
        throw std::logic_error("Each student must have exactly four plants.");
    }

    std::array<kindergarten_garden::Plants, 4U> result{};
    for (std::size_t i{0U}; i < static_cast<std::size_t>(4U); ++i) {
        result[i] = vec[i];
    }
    return result;
}

std::vector<plant> garden::plants(const std::string& student) const {
    const auto it{std::find(m_students.cbegin(), m_students.cend(), student)};
    if (it == m_students.cend()) {
        throw std::invalid_argument("Student not found.");
    }

    const std::size_t index{static_cast<std::size_t>(std::distance(m_students.cbegin(), it))};
    const std::size_t first_col{index * static_cast<std::size_t>(2U)};

    if ((first_col + static_cast<std::size_t>(1U) >= m_rows[0].size()) ||
        (first_col + static_cast<std::size_t>(1U) >= m_rows[1].size())) {
        throw std::out_of_range("Diagram too small for requested student.");
    }

    std::vector<plant> result;
    result.reserve(static_cast<std::size_t>(4U));

    result.push_back(char_to_plant(m_rows[0][first_col]));
    result.push_back(char_to_plant(m_rows[0][first_col + static_cast<std::size_t>(1U)]));
    result.push_back(char_to_plant(m_rows[1][first_col]));
    result.push_back(char_to_plant(m_rows[1][first_col + static_cast<std::size_t>(1U)]));

    return result;
}

}  // namespace kindergarten_garden
kindergarten_garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : m_students{students} {
    std::string current_line{};
    for (const char ch : diagram) {
        if (ch == '\n') {
            if (!current_line.empty()) {
                m_rows.push_back(current_line);
                current_line.clear();
            }
        } else {
            current_line.push_back(ch);
        }
    }
    if (!current_line.empty()) {
        m_rows.push_back(current_line);
    }

    if (m_rows.size() != static_cast<std::size_t>(2U)) {
        throw std::invalid_argument("Diagram must contain exactly two rows.");
    }
}
