#include "kindergarten_garden.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace kindergarten_garden {

garden::garden(const std::string& diagram)
    : students_{ "Alice",  "Bob",    "Charlie", "David",
                 "Eve",    "Fred",   "Ginny",   "Harriet",
                 "Ileana", "Joseph", "Kincaid", "Larry" }
{
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by newline");
    }

    rows_[0U] = diagram.substr(0U, newline_pos);
    rows_[1U] = diagram.substr((newline_pos + 1U));
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_{students}
{
    if (students_.empty()) {
        throw std::invalid_argument("students list must not be empty");
    }

    std::sort(students_.begin(), students_.end());

    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("diagram must contain two rows separated by newline");
    }

    rows_[0U] = diagram.substr(0U, newline_pos);
    rows_[1U] = diagram.substr((newline_pos + 1U));
}

plant garden::char_to_plant(const char c)
{
    if (c == 'C') {
        return plant::clover;
    } else if (c == 'G') {
        return plant::grass;
    } else if (c == 'R') {
        return plant::radishes;
    } else if (c == 'V') {
        return plant::violets;
    } else {
        throw std::invalid_argument("invalid plant character");
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it{std::find_if(
        students_.begin(),
        students_.end(),
        [&student](const std::string& name) { return student == name; })};

    if (it == students_.end()) {
        throw std::invalid_argument("unknown student");
    }

    const std::size_t index{static_cast<std::size_t>(
        std::distance(students_.begin(), it))};
    const std::size_t start{(index * 2U)};

    std::vector<plant> result{};
    result.reserve(4U);

    result.push_back(char_to_plant(rows_[0U][start]));
    result.push_back(char_to_plant(rows_[0U][(start + 1U)]));
    result.push_back(char_to_plant(rows_[1U][start]));
    result.push_back(char_to_plant(rows_[1U][(start + 1U)]));

    return result;
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    const garden g{diagram};
    const std::vector<plant> vec{g.plants(student)};

    std::array<Plants, 4U> arr{};
    for (std::size_t i{0U}; i < 4U; ++i) {
        arr[i] = vec[i];
    }

    return arr;
}

}  // namespace kindergarten_garden
