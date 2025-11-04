#include "kindergarten_garden.h"

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {
constexpr std::array<const char*, 12U> kStudents{
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
}  // namespace

garden::garden(const std::string& diagram) {
    const std::string::size_type pos = diagram.find('\n');
    if (pos == std::string::npos) {
        rows_[0] = diagram;
        rows_[1].clear();
    } else {
        rows_[0] = diagram.substr(0, pos);
        rows_[1] = diagram.substr(pos + static_cast<std::string::size_type>(1));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const {
    const std::size_t idx = garden::student_index(student);
    const std::size_t start = (idx * static_cast<std::size_t>(2));

    std::vector<Plants> result{};
    result.reserve(static_cast<std::vector<Plants>::size_type>(4));

    if ((rows_[0].size() >= (start + static_cast<std::size_t>(2))) &&
        (rows_[1].size() >= (start + static_cast<std::size_t>(2)))) {
        const char a = rows_[0][start];
        const char b = rows_[0][start + static_cast<std::size_t>(1)];
        const char c = rows_[1][start];
        const char d = rows_[1][start + static_cast<std::size_t>(1)];

        result.push_back(garden::char_to_plant(a));
        result.push_back(garden::char_to_plant(b));
        result.push_back(garden::char_to_plant(c));
        result.push_back(garden::char_to_plant(d));
    } else {
        throw std::invalid_argument("Invalid diagram or student index resulting in out-of-range access.");
    }

    return result;
}

std::size_t garden::student_index(const std::string& student) {
    for (std::size_t i = 0U; i < kStudents.size(); ++i) {
        if (student == kStudents[i]) {
            return i;
        }
    }
    throw std::invalid_argument("Unknown student name: " + student);
}

Plants garden::char_to_plant(char c) {
    if (c == 'G') {
        return Plants::grass;
    } else if (c == 'C') {
        return Plants::clover;
    } else if (c == 'R') {
        return Plants::radishes;
    } else if (c == 'V') {
        return Plants::violets;
    } else {
        throw std::invalid_argument("Unknown plant code in diagram.");
    }
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
    const garden g(diagram);
    const std::vector<Plants> v = g.plants(student);
    if ((v.size()) != static_cast<std::vector<Plants>::size_type>(4)) {
        throw std::invalid_argument("Expected exactly four plants for a student.");
    } else {
        // no-op
    }
    std::array<Plants, 4U> out{{v[0], v[1], v[2], v[3]}};
    return out;
}

}  // namespace kindergarten_garden
