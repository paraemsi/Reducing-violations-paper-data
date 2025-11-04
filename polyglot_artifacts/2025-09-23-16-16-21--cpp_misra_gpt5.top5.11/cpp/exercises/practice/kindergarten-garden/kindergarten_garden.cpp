#include "kindergarten_garden.h"

#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {
    const std::vector<std::string> default_students{
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve",
        "Fred",
        "Ginny",
        "Harriet",
        "Ileana",
        "Joseph",
        "Kincaid",
        "Larry"
    };
    constexpr std::size_t cups_per_student{2U};
    constexpr std::size_t plants_per_student{4U};
    constexpr std::size_t cup_offset{1U};
static Plants to_plants(const char code) {
    switch (code) {
        case 'C':
            return Plants::clover;
        case 'G':
            return Plants::grass;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            return Plants::violets;
    }
}

static std::size_t student_index_free(const std::string& student) {
    for (std::size_t i = 0U; i < default_students.size(); i = (i + 1U)) {
        if (default_students[i] == student) {
            return i;
        }
    }
    return 0U;
}
}  // namespace

garden::garden(const std::string& diagram) {
    const std::size_t newline_pos = diagram.find('\n');
    if (newline_pos != std::string::npos) {
        row1_ = diagram.substr(0U, newline_pos);
        row2_ = diagram.substr((newline_pos + 1U));
    } else {
        row1_ = diagram;
        row2_.clear();
    }
}

std::size_t garden::student_index(const std::string& student) {
    for (std::size_t i = 0U; i < default_students.size(); i = (i + 1U)) {
        if (default_students[i] == student) {
            return i;
        }
    }
    return 0U;
}

plant garden::to_plant(const char code) {
    switch (code) {
        case 'C':
            return plant::clover;
        case 'G':
            return plant::grass;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            return plant::violets;
    }
}

std::vector<plant> garden::plants(const std::string& student) const {
    const std::size_t idx = garden::student_index(student);
    const std::size_t start = (idx * cups_per_student);

    std::vector<plant> result{};
    result.reserve(plants_per_student);

    if (row1_.size() >= (start + cups_per_student)) {
        const char c1 = row1_[start];
        const char c2 = row1_[(start + cup_offset)];
        result.push_back(garden::to_plant(c1));
        result.push_back(garden::to_plant(c2));
    }

    if (row2_.size() >= (start + cups_per_student)) {
        const char c3 = row2_[start];
        const char c4 = row2_[(start + cup_offset)];
        result.push_back(garden::to_plant(c3));
        result.push_back(garden::to_plant(c4));
    }

    return result;
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
    std::string row1{};
    std::string row2{};
    const std::size_t newline_pos = diagram.find('\n');
    if (newline_pos != std::string::npos) {
        row1 = diagram.substr(0U, newline_pos);
        row2 = diagram.substr((newline_pos + 1U));
    } else {
        row1 = diagram;
        row2.clear();
    }

    const std::size_t idx = student_index_free(student);
    const std::size_t start = (idx * cups_per_student);

    std::array<Plants, 4U> result{
        Plants::clover, Plants::clover, Plants::clover, Plants::clover
    };

    if (row1.size() >= (start + cups_per_student)) {
        const char c1 = row1[start];
        const char c2 = row1[(start + cup_offset)];
        result[0U] = to_plants(c1);
        result[1U] = to_plants(c2);
    }

    if (row2.size() >= (start + cups_per_student)) {
        const char c3 = row2[start];
        const char c4 = row2[(start + cup_offset)];
        result[2U] = to_plants(c3);
        result[3U] = to_plants(c4);
    }

    return result;
}

}  // namespace kindergarten_garden
