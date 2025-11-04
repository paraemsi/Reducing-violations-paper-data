#include "kindergarten_garden.h"

#include <stdexcept>

namespace kindergarten_garden {

namespace {

/* List of students in alphabetical order as required by the exercise. */
constexpr std::array<const char*, 12U> k_students{
    "Alice", "Bob",   "Charlie", "David",
    "Eve",   "Fred",  "Ginny",   "Harriet",
    "Ileana","Joseph","Kincaid", "Larry"};

}  // unnamed namespace

/* Convert the diagram character to the corresponding plant enum value. */
Plants garden::char_to_plant(char c)
{
    switch (c) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default: {
            throw std::invalid_argument("Invalid plant code in diagram.");
        }
    }
}

garden::garden(std::string_view diagram) : m_student_plants{}
{
    /* Allow (and ignore) an optional leading newline in the diagram. */
    std::string_view clean_diagram{diagram};
    if ((!clean_diagram.empty()) && (clean_diagram.front() == '\n')) {
        clean_diagram.remove_prefix(1U);
    }

    const std::string_view::size_type newline_pos{clean_diagram.find('\n')};
    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument("Diagram must contain exactly two rows.");
    }

    const std::string_view row_one{clean_diagram.substr(0U, newline_pos)};
    const std::string_view row_two{clean_diagram.substr(newline_pos + 1U)};

    if ((row_one.size() != row_two.size())) {
        throw std::invalid_argument("Rows must be of equal length.");
    }

    const std::size_t cups_per_row{row_one.size()};
    if (((cups_per_row % 2U) != 0U)) {
        throw std::invalid_argument("Row length must be even.");
    }

    const std::size_t student_count{cups_per_row / 2U};
    if (student_count > k_students.size()) {
        throw std::invalid_argument("Too many students for predefined list.");
    }

    for (std::size_t i{0U}; i < student_count; ++i) {
        const std::size_t index{i * 2U};

        std::array<Plants, 4U> ps{
            char_to_plant(row_one.at(index)),
            char_to_plant(row_one.at(index + 1U)),
            char_to_plant(row_two.at(index)),
            char_to_plant(row_two.at(index + 1U))};

        m_student_plants.emplace(k_students.at(i), ps);
    }
}

std::vector<Plants> garden::plants(std::string_view student) const
{
    const auto it{m_student_plants.find(std::string(student))};
    if (it == m_student_plants.end()) {
        throw std::out_of_range("Student not found.");
    }

    std::vector<Plants> result;
    result.reserve(it->second.size());
    for (const Plants& p : it->second) {
        result.push_back(p);
    }
    return result;
}

std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student)
{
    garden g{diagram};
    const std::vector<Plants> vec{g.plants(student)};
    std::array<Plants, 4U> arr{};
    for (std::size_t i{0U}; i < arr.size(); ++i) {
        arr[i] = vec.at(i);
    }
    return arr;
}

}  // namespace kindergarten_garden
