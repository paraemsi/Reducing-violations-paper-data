#include "kindergarten_garden.h"

#include <stdexcept>
#include <utility>
#include <algorithm>
#include <array>
#include <cstddef>
#include <string_view>

namespace kindergarten_garden {

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------

const std::vector<std::string> default_students{
    "Alice",  "Bob",    "Charlie", "David",
    "Eve",    "Fred",   "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"};

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace {

Plants char_to_plant(char c)
{
    switch (c) {
        case 'C': return Plants::clover;
        case 'G': return Plants::grass;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument{"Invalid plant code"};
    }
}

std::pair<std::string, std::string> split_rows(const std::string& diagram)
{
    // Determine starting index (skip an optional leading newline).
    std::size_t start = (!diagram.empty() && diagram.front() == '\n') ? 1 : 0;

    // Find the newline that separates the two rows.
    const auto pos = diagram.find('\n', start);
    if (pos == std::string::npos) {
        throw std::invalid_argument{"Diagram must contain two rows"};
    }

    std::string row1 = diagram.substr(start, pos - start);
    std::string row2 = diagram.substr(pos + 1);

    // Trim an optional trailing newline from the second row.
    if (!row2.empty() && row2.back() == '\n') {
        row2.pop_back();
    }

    return {row1, row2};
}

} // namespace

// ---------------------------------------------------------------------------
// garden implementation
// ---------------------------------------------------------------------------

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    auto [row1, row2] = split_rows(diagram);

    std::vector<std::string> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end());

    const std::size_t expected_length = sorted_students.size() * 2;
    if (row1.size() < expected_length || row2.size() < expected_length) {
        throw std::invalid_argument{"Diagram does not contain enough cups"};
    }

    for (std::size_t i = 0; i < sorted_students.size(); ++i) {
        std::array<Plants, 4> assigned{
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])};

        assignments_.emplace(sorted_students[i], assigned);
    }
}

std::array<Plants, 4> garden::plants(std::string_view student_name) const
{
    auto it = assignments_.find(std::string{student_name});
    if (it == assignments_.end()) {
        throw std::out_of_range{"Unknown student"};
    }
    return it->second;
}

std::array<Plants, 4> plants(std::string_view diagram,
                             std::string_view student_name)
{
    garden g(std::string{diagram});
    return g.plants(student_name);
}

}  // namespace kindergarten_garden
