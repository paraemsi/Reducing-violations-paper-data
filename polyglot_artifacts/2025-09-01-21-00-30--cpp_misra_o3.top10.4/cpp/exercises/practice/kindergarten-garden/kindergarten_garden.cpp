#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace kindergarten_garden {

namespace {
/* Constants to avoid magic numbers. */
constexpr std::size_t cups_per_student{static_cast<std::size_t>(4U)};
constexpr std::size_t rows{static_cast<std::size_t>(2U)};
}  // namespace

garden::garden(std::string_view diagram, std::vector<std::string> students)
{
    /* Supply the canonical student order if none was provided. */
    if (students.empty()) {
        students = default_students();
    }

    /* Remove an optional leading newline so the first row starts immediately. */
    std::string_view diag{diagram};
    if (( !diag.empty() ) && ( diag.front() == '\n' )) {
        diag.remove_prefix(1U);
    }

    /* Split the two rows at the first newline. */
    const std::size_t newline_pos{diag.find('\n')};
    if (newline_pos == std::string_view::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by newline");
    }
    const std::string_view row1{diag.substr(0U, newline_pos)};
    const std::string_view row2{diag.substr(newline_pos + 1U)};

    if (row1.size() != row2.size()) {
        throw std::invalid_argument("rows must be equal length");
    }

    const std::size_t expected_length{
        ( students.size() * cups_per_student ) / rows
    };
    if (row1.size() != expected_length) {
        throw std::invalid_argument("row length does not match number of students");
    }

    /* Parse the diagram and populate the map. */
    for (std::size_t i{0U}; i < students.size(); ++i) {
        std::vector<plant> vec{};
        vec.reserve(cups_per_student);

        const std::size_t index{i * static_cast<std::size_t>(2U)};

        vec.push_back(char_to_plant(row1[index]));
        vec.push_back(char_to_plant(row1[index + static_cast<std::size_t>(1U)]));
        vec.push_back(char_to_plant(row2[index]));
        vec.push_back(char_to_plant(row2[index + static_cast<std::size_t>(1U)]));

        student_plants_.emplace(students[i], vec);
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it{student_plants_.find(student)};
    if (it == student_plants_.end()) {
        return {};
    }
    return it->second;
}

plant garden::char_to_plant(char c)
{
    switch (c) {
        case 'G':
            return plant::grass;
        case 'C':
            return plant::clover;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            throw std::invalid_argument("invalid plant code");
    }
}

std::vector<std::string> garden::default_students()
{
    return { "Alice",  "Bob",     "Charlie", "David",
             "Eve",    "Fred",    "Ginny",   "Harriet",
             "Ileana", "Joseph",  "Kincaid", "Larry" };
}

/* Free helper fulfilling the public API expected by the tests. */
std::array<Plants, static_cast<std::size_t>(4U)>
plants(std::string_view diagram,
       std::string_view student,
       std::vector<std::string> students)
{
    garden g{diagram, std::move(students)};
    const std::vector<plant> vec{g.plants(std::string{student})};

    std::array<Plants, static_cast<std::size_t>(4U)> result{};
    for (std::size_t i{0U}; (i < result.size()) && (i < vec.size()); ++i) {
        /* Same underlying enumeration – explicit cast satisfies MISRA. */
        result[i] = static_cast<Plants>(vec[i]);
    }
    return result;
}

}  // namespace kindergarten_garden
