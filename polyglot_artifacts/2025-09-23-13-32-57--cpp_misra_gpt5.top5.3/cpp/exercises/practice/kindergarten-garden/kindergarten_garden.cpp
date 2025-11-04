#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace kindergarten_garden {

namespace {
constexpr std::array<const char*, 12U> kStudents = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};
}  // namespace

garden::garden(const std::string& diagram) {
    const std::size_t pos = diagram.find('\n');
    if ((pos != std::string::npos)) {
        row1_ = std::string(diagram.substr(0U, pos));
        row2_ = std::string(diagram.substr((pos + static_cast<std::size_t>(1U))));
    } else {
        row1_ = std::string(diagram);
        row2_.clear();
    }
}

std::array<Plants, 4U> garden::plants(const std::string& student) const {
    const std::size_t idx = garden::student_index(student);
    const std::size_t base = (static_cast<std::size_t>(2U) * idx);

    std::array<Plants, 4U> result = {
        garden::to_plant(row1_.at(base)),
        garden::to_plant(row1_.at(base + static_cast<std::size_t>(1U))),
        garden::to_plant(row2_.at(base)),
        garden::to_plant(row2_.at(base + static_cast<std::size_t>(1U)))
    };

    return result;
}

Plants garden::to_plant(char code) noexcept {
    if ((code == 'G')) {
        return Plants::grass;
    } else {
        if ((code == 'C')) {
            return Plants::clover;
        } else {
            if ((code == 'R')) {
                return Plants::radishes;
            } else {
                return Plants::violets;
            }
        }
    }
}

std::size_t garden::student_index(const std::string& student) noexcept {
    for (std::size_t i = static_cast<std::size_t>(0U); (i < kStudents.size()); ++i) {
        if ((student == kStudents.at(i))) {
            return i;
        }
    }
    return static_cast<std::size_t>(0U);
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
    garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
