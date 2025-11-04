#include "kindergarten_garden.h"

#include <algorithm>
#include <utility>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace {

// Split the two rows of the diagram at the newline.
std::pair<std::string, std::string> split_rows(const std::string& diagram)
{
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("diagram must contain a newline separating two rows");
    }

    return std::make_pair(diagram.substr(0U, newline_pos),
                          diagram.substr(newline_pos + 1U));
}

}  // namespace

// Convert a character in the diagram to its corresponding plant.
Plants garden::char_to_plant(char symbol)
{
    switch (symbol)
    {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("invalid plant symbol in diagram");
    }
}

// Default, alphabetically ordered list of students.
std::vector<std::string> garden::default_students()
{
    return { "Alice",  "Bob",     "Charlie", "David",
             "Eve",    "Fred",    "Ginny",   "Harriet",
             "Ileana", "Joseph",  "Kincaid", "Larry" };
}

// Constructor with default students.
garden::garden(const std::string& diagram)
    : garden(diagram, default_students())
{
    // Delegates to the main constructor.
}

// Constructor with explicit student list.
garden::garden(const std::string&      diagram,
               const std::vector<std::string>& students)
{
    const auto rows{split_rows(diagram)};
    const std::string& first_row{rows.first};
    const std::string& second_row{rows.second};

    // Validate that the diagram has an even number of cups per row.
    if ((first_row.length() % 2U) != 0U)
    {
        throw std::invalid_argument("each row in diagram must contain an even number of cups");
    }

    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    const std::size_t cup_pairs{first_row.length() / 2U};
    if (cup_pairs != sorted_students.size())
    {
        throw std::invalid_argument("number of students does not match diagram width");
    }

    // Assign plants to students in alphabetical order.
    for (std::size_t i{0U}; i < sorted_students.size(); ++i)
    {
        const std::size_t col{2U * i};

        std::vector<Plants> assigned{
            char_to_plant(first_row[col]),
            char_to_plant(first_row[col + 1U]),
            char_to_plant(second_row[col]),
            char_to_plant(second_row[col + 1U])};

        m_assignments.emplace(sorted_students[i], std::move(assigned));
    }
}

// Retrieve plants for a student.
std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it{m_assignments.find(student)};
    if (it == m_assignments.end())
    {
        throw std::out_of_range("student not found in garden");
    }

    return it->second;
}

// Convenience free function required by tests.
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g{diagram};
    const auto    vec{g.plants(student)};

    std::array<Plants, 4U> arr{};
    for (std::size_t i{0U}; i < 4U; ++i)
    {
        arr[i] = vec[i];
    }
    return arr;
}

}  // namespace kindergarten_garden
