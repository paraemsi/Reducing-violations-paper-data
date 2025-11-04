#include "kindergarten_garden.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <array>
#include <utility>   // for std::move

namespace {
// Convert one diagram character to a Plant
[[nodiscard]] kindergarten_garden::Plants char_to_plant(char symbol)
{
    if (symbol == 'V') {
        return kindergarten_garden::Plants::violets;
    }
    if (symbol == 'R') {
        return kindergarten_garden::Plants::radishes;
    }
    if (symbol == 'C') {
        return kindergarten_garden::Plants::clover;
    }
    if (symbol == 'G') {
        return kindergarten_garden::Plants::grass;
    }

    throw std::invalid_argument("Unknown plant code in diagram.");
}
} // unnamed namespace

namespace kindergarten_garden {

// ---------- helpers ---------------------------------------------------------

const std::vector<std::string>& garden::default_student_list()
{
    static const std::vector<std::string> default_names{
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
    return default_names;
}

 // ---------- constructor -----------------------------------------------------

garden::garden(const std::string& diagram)
    : garden(diagram, default_student_list())
{
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    // Build the roster
    std::vector<std::string> roster;
    if (students.empty()) {
        roster = default_student_list();
    } else {
        roster = students;
    }
    std::sort(roster.begin(), roster.end());

    // Split diagram into its two non-empty rows
    std::vector<std::string> rows;
    {
        std::istringstream row_stream(diagram);
        std::string line;
        while (std::getline(row_stream, line)) {
            if (!line.empty()) {
                rows.push_back(line);
            }
        }
    }

    if (rows.size() != static_cast<std::size_t>(2)) {
        throw std::invalid_argument("Diagram must contain exactly two non-empty rows.");
    }

    const std::string& first_row  = rows[0];
    const std::string& second_row = rows[1];
    const std::size_t  expected   = roster.size() * static_cast<std::size_t>(2);

    if ((first_row.length() != expected) ||
        (second_row.length() != expected)) {
        throw std::invalid_argument("Row length mismatch with student count.");
    }

    // Assign plants to each student
    for (std::size_t idx = static_cast<std::size_t>(0); idx < roster.size(); ++idx) {
        std::array<Plants, 4U> four_cups{};

        const std::size_t column = idx * static_cast<std::size_t>(2);
        four_cups[0U] = char_to_plant(first_row[column]);
        four_cups[1U] = char_to_plant(first_row[column + static_cast<std::size_t>(1)]);
        four_cups[2U] = char_to_plant(second_row[column]);
        four_cups[3U] = char_to_plant(second_row[column + static_cast<std::size_t>(1)]);

        (void)assignments_.emplace(roster[idx], std::move(four_cups));
    }
}

// ---------- query -----------------------------------------------------------

std::array<Plants, 4> garden::plants(const std::string& student) const
{
    const auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range("Student not found.");
    }

    return it->second;
}

 // ---------- free helper functions ------------------------------------------

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student)
{
    const garden g(diagram);
    return g.plants(student);
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::vector<std::string>& students,
                             const std::string& student)
{
    const garden g(diagram, students);
    return g.plants(student);
}

}  // namespace kindergarten_garden
