#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <stdexcept>

namespace kindergarten_garden {

// ---------------------------------------------------------------------------
// Helper: translate diagram character to plant enum
// ---------------------------------------------------------------------------
static Plants char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default: throw std::invalid_argument("Invalid plant code in diagram");
    }
}

// ---------------------------------------------------------------------------
// Definition of static default roster
// ---------------------------------------------------------------------------
const std::vector<std::string> garden::default_students_{
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

// ---------------------------------------------------------------------------
// garden constructor – parses the diagram into student assignments
// ---------------------------------------------------------------------------
garden::garden(const std::string& diagram,
               const std::vector<std::string>& students) {
    // Split diagram into its two mandatory rows.
    std::istringstream iss(diagram);
    std::string row1, row2;
    std::getline(iss, row1);
    std::getline(iss, row2);

    if (row2.empty()) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    // Establish the roster.
    // If no custom list is supplied we take just as many of the default
    // students as are required by the diagram length (two cups per student).
    std::vector<std::string> roster;
    if (students.empty()) {
        if (row1.size() % 2 != 0 || row2.size() != row1.size()) {
            throw std::invalid_argument("Rows must be equal length and even");
        }
        std::size_t num_students = row1.size() / 2;
        if (num_students > default_students_.size()) {
            throw std::invalid_argument("Diagram has more students than default roster");
        }
        roster.assign(default_students_.begin(),
                      default_students_.begin() + static_cast<long>(num_students));
    } else {
        roster = students;
        std::sort(roster.begin(), roster.end());
        const std::size_t expected_length = roster.size() * 2;
        if (row1.size() != expected_length || row2.size() != expected_length) {
            throw std::invalid_argument("Diagram length does not match number of students");
        }
    }

    // Build assignments_ map.
    for (std::size_t i = 0; i < roster.size(); ++i) {
        std::vector<Plants> four;
        four.reserve(4);
        four.push_back(char_to_plant(row1[2 * i]));
        four.push_back(char_to_plant(row1[2 * i + 1]));
        four.push_back(char_to_plant(row2[2 * i]));
        four.push_back(char_to_plant(row2[2 * i + 1]));
        assignments_.emplace(roster[i], std::move(four));
    }
}

// ---------------------------------------------------------------------------
// Retrieve a student's plants.
// ---------------------------------------------------------------------------
std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::invalid_argument("Student not found in garden");
    }
    return it->second;  // return copy as small fixed-size vector
}

// ---------------------------------------------------------------------------
// Free helper function expected by the tests
// ---------------------------------------------------------------------------
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    std::array<Plants, 4> out{};
    std::copy(vec.begin(), vec.end(), out.begin());
    return out;
}

}  // namespace kindergarten_garden
