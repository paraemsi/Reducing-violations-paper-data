#include "kindergarten_garden.h"

namespace kindergarten_garden {

namespace {

[[nodiscard]] Plants char_to_plant(char cup) {
    if((cup == 'G')) {
        return Plants::grass;
    } else if((cup == 'C')) {
        return Plants::clover;
    } else if((cup == 'R')) {
        return Plants::radishes;
    } else if((cup == 'V')) {
        return Plants::violets;
    } else {
        return Plants::grass;  // Fallback; unreachable for valid input
    }
}

}  // unnamed namespace

const std::vector<std::string>& garden::default_students() {
    static const std::vector<std::string> default_list = {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"};
    return default_list;
}

garden::garden(std::string_view diagram, const std::vector<std::string>& students) {
    const std::size_t newline_pos = diagram.find('\n');
    const std::string_view row1 = diagram.substr(0U, newline_pos);
    const std::string_view row2 = (newline_pos != std::string_view::npos)
                                      ? diagram.substr((newline_pos + 1U))
                                      : std::string_view{};

    const std::size_t child_count = students.size();
    for (std::size_t idx = 0U; idx < child_count; ++idx) {
        std::vector<Plants> child_plants;
        child_plants.reserve(4U);

        const std::size_t start = (idx * 2U);

        if (((start + 1U) < row1.size())) {
            child_plants.emplace_back(char_to_plant(row1.at(start)));
            child_plants.emplace_back(char_to_plant(row1.at((start + 1U))));
        }

        if (((start + 1U) < row2.size())) {
            child_plants.emplace_back(char_to_plant(row2.at(start)));
            child_plants.emplace_back(char_to_plant(row2.at((start + 1U))));
        }

        m_assignments.emplace(students.at(idx), std::move(child_plants));
    }
}

std::vector<Plants> garden::plants(std::string_view student) const {
    const auto it = m_assignments.find(std::string(student));
    if (it != m_assignments.end()) {
        return it->second;
    } else {
        return {};
    }
}

std::array<Plants, 4U> plants(std::string_view diagram, std::string_view student) {
    const garden g(diagram);
    const std::vector<Plants> vec = g.plants(student);

    std::array<Plants, 4U> result{};
    for (std::size_t i = 0U; (i < 4U) && (i < vec.size()); ++i) {
        result.at(i) = vec.at(i);
    }
    return result;
}

}  // namespace kindergarten_garden
