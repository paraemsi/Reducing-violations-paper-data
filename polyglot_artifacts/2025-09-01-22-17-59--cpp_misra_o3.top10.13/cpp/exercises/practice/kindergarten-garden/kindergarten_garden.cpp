#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>
#include <iterator>

namespace kindergarten_garden {

namespace {
constexpr std::uint32_t cups_per_student{2U};      // two cups per row
constexpr std::uint32_t rows{2U};
constexpr std::uint32_t plants_per_student{rows * cups_per_student};
}  // namespace

constexpr Plants to_plants(plant p) noexcept {
    if (p == plant::grass) {
        return Plants::grass;
    } else if (p == plant::clover) {
        return Plants::clover;
    } else if (p == plant::radishes) {
        return Plants::radishes;
    } else {  // p == plant::violets
        return Plants::violets;
    }
}

std::vector<std::string> garden::default_students() {
    return {"Alice",   "Bob",   "Charlie", "David",  "Eve",    "Fred",
            "Ginny",   "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
}

plant garden::decode_plant(char code) {
    if (code == 'G') {
        return plant::grass;
    } else if (code == 'C') {
        return plant::clover;
    } else if (code == 'R') {
        return plant::radishes;
    } else if (code == 'V') {
        return plant::violets;
    } else {
        throw std::invalid_argument("Unknown plant code");
    }
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_{students} {
    auto pos{diagram.find('\n')};
    if (pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by newline");
    }

    row1_ = diagram.substr(0U, pos);
    row2_ = diagram.substr((pos + 1U));

    std::sort(students_.begin(), students_.end());
}

std::vector<plant> garden::plants(const std::string& student) const {
    auto it{std::find(students_.cbegin(), students_.cend(), student)};
    if (it == students_.cend()) {
        throw std::invalid_argument("Student not found");
    }

    const std::uint32_t index{static_cast<std::uint32_t>(std::distance(students_.cbegin(), it))};
    const std::uint32_t first_cup{index * cups_per_student};

    std::vector<plant> result{};
    result.reserve(plants_per_student);

    result.push_back(decode_plant(row1_.at(first_cup)));
    result.push_back(decode_plant(row1_.at((first_cup + 1U))));
    result.push_back(decode_plant(row2_.at(first_cup)));
    result.push_back(decode_plant(row2_.at((first_cup + 1U))));

    return result;
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students) {
    const garden g{diagram, students};
    const std::vector<plant> vec{g.plants(student)};

    std::array<Plants, 4U> result{};
    for (std::uint32_t i{0U}; (i < 4U); ++i) {
        result[i] = to_plants(vec[i]);
    }
    return result;
}

}  // namespace kindergarten_garden
