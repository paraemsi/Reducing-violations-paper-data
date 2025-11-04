#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {

constexpr std::array<const char*, 12U> default_students{
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

Plants decode_char(const char c) {
    switch (c) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("Unknown plant code");
    }
}

std::size_t student_index(const std::string& name) {
    for (std::size_t i = 0U; i < default_students.size(); ++i) {
        if (name == default_students[i]) {
            return i;
        }
    }
    throw std::invalid_argument("Unknown student name");
}

}  // namespace

garden::garden(const std::string& diagram) {
    const std::size_t nl = diagram.find('\n');
    if (nl != std::string::npos) {
        row1_ = diagram.substr(0U, nl);
        row2_ = diagram.substr(nl + static_cast<std::size_t>(1));
    } else {
        row1_ = diagram;
        row2_.clear();
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const std::size_t idx = student_index(student);
    const std::size_t start = idx * static_cast<std::size_t>(2);

    std::vector<Plants> result;
    if ((row1_.size() > (start + static_cast<std::size_t>(1))) && (row2_.size() > (start + static_cast<std::size_t>(1)))) {
        result.reserve(static_cast<std::size_t>(4));
        const char c1 = row1_[start];
        const char c2 = row1_[start + static_cast<std::size_t>(1)];
        const char c3 = row2_[start];
        const char c4 = row2_[start + static_cast<std::size_t>(1)];

        result.push_back(decode_char(c1));
        result.push_back(decode_char(c2));
        result.push_back(decode_char(c3));
        result.push_back(decode_char(c4));
    } else {
        // Insufficient data for the requested student; return an empty vector.
    }

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
    std::array<Plants, 4> result{};
    std::string row1;
    std::string row2;

    const std::size_t nl = diagram.find('\n');
    if (nl != std::string::npos) {
        row1 = diagram.substr(0U, nl);
        row2 = diagram.substr(nl + static_cast<std::size_t>(1));
    } else {
        row1 = diagram;
        row2.clear();
    }

    const std::size_t idx = student_index(student);
    const std::size_t start = idx * static_cast<std::size_t>(2);

    if ((row1.size() > (start + static_cast<std::size_t>(1))) && (row2.size() > (start + static_cast<std::size_t>(1)))) {
        result[0] = decode_char(row1[start]);
        result[1] = decode_char(row1[start + static_cast<std::size_t>(1)]);
        result[2] = decode_char(row2[start]);
        result[3] = decode_char(row2[start + static_cast<std::size_t>(1)]);
    } else {
        // Insufficient data; return default-initialized array.
    }

    return result;
}

}  // namespace kindergarten_garden
