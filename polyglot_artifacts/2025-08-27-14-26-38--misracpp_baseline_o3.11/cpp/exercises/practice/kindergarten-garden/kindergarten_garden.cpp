#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

// Initialise the static default roster.
const std::vector<std::string> garden::default_students{
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

garden::garden(std::string_view diagram,
               const std::vector<std::string>& students)
{
    // Split the diagram into two rows; ignore any leading/trailing newlines.
    std::string_view trimmed = diagram;
    if (!trimmed.empty() && trimmed.front() == '\n') {
        trimmed.remove_prefix(1);
    }
    if (!trimmed.empty() && trimmed.back() == '\n') {
        trimmed.remove_suffix(1);
    }

    auto newline_pos = trimmed.find('\n');
    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument("diagram must contain two rows");
    }
    std::string_view row1 = trimmed.substr(0, newline_pos);
    std::string_view row2 = trimmed.substr(newline_pos + 1);

    if (row1.size() != row2.size() || row1.size() % 2 != 0) {
        throw std::invalid_argument("invalid diagram width");
    }

    // Work with a local copy of the roster and ensure it is sorted.
    std::vector<std::string> roster = students;
    std::sort(roster.begin(), roster.end());

    std::size_t expected_width = roster.size() * 2;
    if (row1.size() != expected_width) {
        throw std::invalid_argument("diagram width does not match roster");
    }

    // Build the map: each student gets two cups from each row.
    for (std::size_t i = 0; i < roster.size(); ++i) {
        std::vector<plant> ps;
        ps.reserve(4);

        std::size_t col = i * 2;
        ps.push_back(char_to_plant(row1[col]));
        ps.push_back(char_to_plant(row1[col + 1]));
        ps.push_back(char_to_plant(row2[col]));
        ps.push_back(char_to_plant(row2[col + 1]));

        assignments_.emplace(roster[i], std::move(ps));
    }
}

const std::vector<plant>& garden::plants(std::string_view student) const
{
    auto it = assignments_.find(std::string(student));
    if (it == assignments_.end()) {
        throw std::out_of_range("unknown student");
    }
    return it->second;
}

plant garden::char_to_plant(char c)
{
    switch (c) {
        case 'G': return plant::grass;
        case 'C': return plant::clover;
        case 'R': return plant::radishes;
        case 'V': return plant::violets;
        default:
            throw std::invalid_argument("invalid plant character");
    }
}

std::array<Plants, 4> plants(std::string_view diagram,
                             std::string_view student)
{
    // Create a garden with the default roster (the tests rely on the default).
    garden g{diagram};
    const auto& vec = g.plants(student);

    std::array<Plants, 4> result{};
    std::copy(vec.begin(), vec.end(), result.begin());
    return result;
}

}  // namespace kindergarten_garden
