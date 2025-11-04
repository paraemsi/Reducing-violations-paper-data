#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <array>

namespace kindergarten_garden {

std::vector<std::string> garden::default_students()
{
    return {
        "Alice",   "Bob",     "Charlie", "David",
        "Eve",     "Fred",    "Ginny",   "Harriet",
        "Ileana",  "Joseph",  "Kincaid", "Larry"
    };
}

Plants garden::char_to_plant(char cup)
{
    /* Equality comparisons on character operands are permitted
       under the given MISRA subset. */
    if (cup == 'G') {
        return Plants::grass;
    } else if (cup == 'C') {
        return Plants::clover;
    } else if (cup == 'R') {
        return Plants::radishes;
    } else if (cup == 'V') {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(std::string_view diagram, std::vector<std::string> students)
{
    if (students.empty()) {
        students = default_students();
    }

    std::sort(students.begin(), students.end());

    const std::string diag(diagram);
    const std::size_t newline_pos{diag.find('\n')};

    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    }

    const std::string row1{diag.substr(0U, newline_pos)};
    const std::string row2{diag.substr((newline_pos + 1U))};

    if ((row1.length() != row2.length())) {
        throw std::invalid_argument("Rows must be of equal length");
    }

    const std::size_t cups_per_student{2U};
    const std::size_t expected_length{students.size() * cups_per_student};

    if (row1.length() != expected_length) {
        throw std::invalid_argument("Row length does not match number of students");
    }

    for (std::size_t idx{0U}; idx < students.size(); ++idx) {
        const std::size_t column{idx * cups_per_student};

        std::vector<Plants> child_plants;
        child_plants.reserve(4U);

        child_plants.push_back(char_to_plant(row1[column]));
        child_plants.push_back(char_to_plant(row1[(column + 1U)]));
        child_plants.push_back(char_to_plant(row2[column]));
        child_plants.push_back(char_to_plant(row2[(column + 1U)]));

        assignments_.emplace(students[idx], std::move(child_plants));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it{assignments_.find(student)};
    if (it == assignments_.end()) {
        return {};
    }

    return it->second;
}

std::array<Plants, 4U> plants(std::string_view diagram,
                              std::string_view student,
                              std::vector<std::string> students)
{
    garden g(diagram, std::move(students));
    const std::vector<Plants> vec{g.plants(std::string(student))};

    std::array<Plants, 4U> result{};
    std::copy(vec.begin(), vec.end(), result.begin());
    return result;
}

}  // namespace kindergarten_garden
