#include "kindergarten_garden.h"

#include <sstream>
#include <stdexcept>
#include <array>
#include <algorithm>

namespace kindergarten_garden {
namespace {

// Helper constant for clarity.
constexpr char newline = '\n';

}  // namespace

// ----- private helper utilities ------------------------------------------- //
std::vector<std::string> garden::default_students() {
    return { "Alice",  "Bob",   "Charlie", "David",
             "Eve",    "Fred",  "Ginny",   "Harriet",
             "Ileana", "Joseph","Kincaid", "Larry" };
}

// ------------------------------------------------------------------------- //
// Free helper functions demanded by the tests                               //
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student) {
    garden g(diagram);
    auto vec = g.plants(student);
    if (vec.size() != 4) {
        throw std::logic_error("Each student must have exactly four plants");
    }
    std::array<Plants, 4> arr;
    std::copy(vec.begin(), vec.end(), arr.begin());
    return arr;
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students) {
    garden g(diagram, students);
    auto vec = g.plants(student);
    if (vec.size() != 4) {
        throw std::logic_error("Each student must have exactly four plants");
    }
    std::array<Plants, 4> arr;
    std::copy(vec.begin(), vec.end(), arr.begin());
    return arr;
}

Plants garden::char_to_plant(char c) {
    switch (c) {
        case 'G': return Plants::grass;
        case 'C': return Plants::clover;
        case 'R': return Plants::radishes;
        case 'V': return Plants::violets;
        default:
            throw std::invalid_argument("Invalid plant code in diagram");
    }
}

// ----- ctors --------------------------------------------------------------- //
garden::garden(const std::string& diagram)
    : students_(default_students()) {
    assign(diagram);
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
    : students_(students) {
    std::sort(students_.begin(), students_.end());
    assign(diagram);
}

// ----- public API ---------------------------------------------------------- //
std::vector<Plants> garden::plants(const std::string& student) const {
    auto it = assignments_.find(student);
    if (it == assignments_.end()) {
        throw std::out_of_range("Unknown student: " + student);
    }
    return it->second;
}

// ----- internal logic ------------------------------------------------------ //
void garden::assign(const std::string& diagram) {
    // Strip a possible leading newline for convenience.
    std::string clean = diagram;
    if (!clean.empty() && clean.front() == newline) {
        clean.erase(clean.begin());
    }

    std::istringstream ss(clean);
    std::string row1, row2;
    std::getline(ss, row1);
    std::getline(ss, row2);

    if (row1.empty() || row2.empty()) {
        throw std::invalid_argument("Diagram must contain exactly two rows");
    }

    // Validate diagram width and adapt the implicit student list length
    if (row1.size() != row2.size() || row1.size() % 2 != 0) {
        throw std::invalid_argument("Diagram must have two rows of equal even length");
    }

    std::size_t student_count = row1.size() / 2;

    // If the caller used the default alphabetic list, we may need to truncate it
    if (students_.size() > student_count) {
        students_.resize(student_count);
    }

    // Otherwise, if they supplied fewer students than the diagram encodes, fail
    if (students_.size() < student_count) {
        throw std::invalid_argument("Diagram encodes more students than supplied");
    }

    for (std::size_t i = 0; i < student_count; ++i) {
        std::vector<Plants> p {
            char_to_plant(row1[2 * i]),
            char_to_plant(row1[2 * i + 1]),
            char_to_plant(row2[2 * i]),
            char_to_plant(row2[2 * i + 1])
        };
        assignments_.emplace(students_[i], std::move(p));
    }
}

}  // namespace kindergarten_garden
