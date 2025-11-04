#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <array>

namespace kindergarten_garden {

namespace {

/* Convert diagram string into two vector lines without the leading newline if present */
std::pair<std::string, std::string> split_rows(const std::string& diagram)
{
    auto first_line_start = (diagram.front() == '\n') ? static_cast<std::size_t>(1U) : static_cast<std::size_t>(0U);
    auto newline_pos      = diagram.find('\n', first_line_start);
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    }

    const std::string row1 = diagram.substr(first_line_start, (newline_pos - first_line_start));
    const std::string row2 = diagram.substr((newline_pos + static_cast<std::size_t>(1U)));

    if (row1.size() != row2.size()) {
        throw std::invalid_argument("rows must be of equal length");
    }

    return {row1, row2};
}

}  // namespace

/* ---------- kindergarten implementation ---------------------------------- */

kindergarten::kindergarten(const std::string& diagram, const std::vector<std::string>& students)
{
    const auto [row1, row2] = split_rows(diagram);

    if ((row1.size() % static_cast<std::size_t>(2U)) != static_cast<std::size_t>(0U)) {
        throw std::invalid_argument("each row must have an even number of cups");
    }

    if (students.empty()) {
        throw std::invalid_argument("students list must not be empty");
    }

    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    const std::size_t expected_cups = static_cast<std::size_t>(2U) * sorted_students.size();
    if (row1.size() != expected_cups) {
        throw std::invalid_argument("row length does not match number of students");
    }

    for (std::size_t idx = static_cast<std::size_t>(0U); idx < sorted_students.size(); ++idx) {
        const std::size_t col = static_cast<std::size_t>(2U) * idx;

        const plant p1 = to_plant(row1[col]);
        const plant p2 = to_plant(row1[col + static_cast<std::size_t>(1U)]);
        const plant p3 = to_plant(row2[col]);
        const plant p4 = to_plant(row2[col + static_cast<std::size_t>(1U)]);

        m_lookup.emplace(sorted_students[idx], std::vector<plant>{p1, p2, p3, p4});
    }
}

std::vector<std::string> kindergarten::default_students()
{
    return {"Alice",  "Bob",  "Charlie", "David",   "Eve",  "Fred",
            "Ginny",  "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
}

plant kindergarten::to_plant(char code)
{
    switch (code) {
    case 'C':
        return plant::clover;
    case 'G':
        return plant::grass;
    case 'R':
        return plant::radishes;
    case 'V':
        return plant::violets;
    default:
        throw std::invalid_argument("invalid plant code");
    }
}

std::vector<plant> kindergarten::plants(const std::string& student) const
{
    const auto it = m_lookup.find(student);
    if (it == m_lookup.end()) {
        return {};
    }
    return it->second;
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    /* Determine how many students are implied by the diagram.
       The diagram must contain two rows separated by a single '\n'. */
    const std::size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    }

    const std::size_t cups_in_row = newline_pos;                 /* row length */
    if ((cups_in_row % static_cast<std::size_t>(2U)) != static_cast<std::size_t>(0U)) {
        throw std::invalid_argument("row must contain an even number of cups");
    }

    const std::size_t student_count = cups_in_row / static_cast<std::size_t>(2U);

    /* Take the first `student_count` names from the canonical student list */
    auto all_students = kindergarten::default_students();
    if (student_count > all_students.size()) {
        throw std::invalid_argument("diagram specifies more students than available");
    }
    all_students.resize(student_count);

    /* Build the garden with the appropriate subset */
    const kindergarten kg(diagram, all_students);

    const auto vec = kg.plants(student);
    if (vec.size() != static_cast<std::size_t>(4U)) {
        throw std::logic_error("invalid number of plants for student");
    }

    std::array<Plants, 4U> result{};
    for (std::size_t i = static_cast<std::size_t>(0U); i < static_cast<std::size_t>(4U); ++i) {
        result[i] = vec[i];
    }
    return result;
}

}  // namespace kindergarten_garden
