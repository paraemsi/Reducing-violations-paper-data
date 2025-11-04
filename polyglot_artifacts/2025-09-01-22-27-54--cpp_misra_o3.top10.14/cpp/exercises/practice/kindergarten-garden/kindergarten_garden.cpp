#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>
#include <cstddef>   // for std::size_t

namespace kindergarten_garden {

namespace {

constexpr std::size_t cups_per_student{2U};
constexpr std::size_t rows_in_diagram{2U};

[[nodiscard]] Plants char_to_plant(char ch)
{
    /* Equality comparisons on characters are permitted by the rule set.
       A chain of if-else statements avoids the implicit integral
       conversion that a switch statement would require, thereby fully
       adhering to “The numerical value of a character shall not be used”. */
    if (ch == 'G') {
        return Plants::grass;
    } else if (ch == 'C') {
        return Plants::clover;
    } else if (ch == 'R') {
        return Plants::radishes;
    } else if (ch == 'V') {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Invalid plant code in diagram.");
    }
}

}  // namespace

Garden::Garden(const std::string& diagram, const std::vector<std::string>& students)
{
    /* Copy and sort student list alphabetically as required. */
    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    /* Locate the two rows, skipping any leading newline that Exercism diagrams include. */
    std::size_t start_index{0U};
    if ((diagram.size() > 0U) && (diagram[0U] == '\n')) {
        start_index = 1U;
    }

    const std::size_t newline_pos{diagram.find('\n', start_index)};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by newline.");
    }

    const std::string first_row{diagram.substr(start_index, (newline_pos - start_index))};
    const std::string second_row{diagram.substr((newline_pos + 1U))};

    const std::size_t expected_length{cups_per_student * sorted_students.size()};
    if ((first_row.length() != expected_length) || (second_row.length() != expected_length)) {
        throw std::invalid_argument("Diagram rows do not match expected length.");
    }

    for (std::size_t idx{0U}; idx < sorted_students.size(); ++idx) {
        const std::size_t offset{idx * cups_per_student};

        std::vector<Plants> plant_list;
        plant_list.reserve(rows_in_diagram * cups_per_student);

        plant_list.push_back(char_to_plant(first_row[offset]));
        plant_list.push_back(char_to_plant(first_row[offset + 1U]));
        plant_list.push_back(char_to_plant(second_row[offset]));
        plant_list.push_back(char_to_plant(second_row[offset + 1U]));

        const auto result{m_student_plants.emplace(sorted_students[idx], plant_list)};
        if (!result.second) {
            throw std::invalid_argument("Duplicate student name encountered.");
        }
    }
}

std::vector<Plants> Garden::plants(const std::string& student) const
{
    const auto it{m_student_plants.find(student)};
    if (it == m_student_plants.end()) {
        throw std::out_of_range("Student name not found.");
    }
    return it->second;
}

/* Free-function wrapper required by the tests. */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    /* Determine how many students are represented by the diagram.
       The first (window-side) row appears first in the string. */
    std::size_t start_index{0U};
    if ((diagram.size() > 0U) && (diagram[0U] == '\n')) {
        start_index = 1U;
    }
    const std::size_t newline_pos{diagram.find('\n', start_index)};
    const std::size_t first_row_len{(newline_pos == std::string::npos) ? 0U
                                                                       : (newline_pos - start_index)};

    if ((first_row_len == 0U) || ((first_row_len % cups_per_student) != 0U)) {
        throw std::invalid_argument("Diagram row length is invalid.");
    }

    const std::size_t student_count{first_row_len / cups_per_student};

    /* Default alphabetical list of all possible students. */
    static const std::array<std::string, 12U> default_names{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };

    if (student_count > default_names.size()) {
        throw std::invalid_argument("Diagram contains more students than supported.");
    }

    std::vector<std::string> chosen_students{default_names.begin(),
                                             default_names.begin() + static_cast<std::ptrdiff_t>(student_count)};

    const Garden g{diagram, chosen_students};
    const std::vector<Plants> vec{g.plants(student)};

    if (vec.size() != 4U) {
        throw std::logic_error("Each student must have exactly four plants.");
    }

    std::array<Plants, 4U> arr{};
    for (std::size_t i{0U}; i < 4U; ++i) {
        arr[i] = vec[i];
    }
    return arr;
}

}  // namespace kindergarten_garden
