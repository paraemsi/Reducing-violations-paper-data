#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace kindergarten_garden {

namespace {
constexpr std::array<const char*, static_cast<std::size_t>(12U)> kStudents{
    "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
    "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
};

inline Plants char_to_plant(const char ch)
{
    if (ch == 'G') {
        return Plants::grass;
    } else if (ch == 'C') {
        return Plants::clover;
    } else if (ch == 'R') {
        return Plants::radishes;
    } else if (ch == 'V') {
        return Plants::violets;
    } else {
        // Unknown plant code; this path should not occur with valid input.
        // Choose a default or raise an exception; we throw for clarity.
        throw std::invalid_argument("Unknown plant code");
    }
}
}  // namespace

garden::garden(const std::string& diagram)
{
    const std::string::size_type newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        rows_[static_cast<std::size_t>(0U)] = diagram;
        rows_[static_cast<std::size_t>(1U)].clear();
    } else {
        rows_[static_cast<std::size_t>(0U)] = diagram.substr(static_cast<std::string::size_type>(0U), newline_pos);
        rows_[static_cast<std::size_t>(1U)] = diagram.substr((newline_pos + static_cast<std::string::size_type>(1U)));
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    // Find the student's index in the predefined order without mixing signed/unsigned
    std::string::size_type index = static_cast<std::string::size_type>(0U);
    bool found = false;
    for (std::string::size_type i = static_cast<std::string::size_type>(0U);
         i < static_cast<std::string::size_type>(kStudents.size());
         i = (i + static_cast<std::string::size_type>(1U))) {
        if (student == std::string{kStudents[static_cast<std::size_t>(i)]}) {
            index = i;
            found = true;
            break;
        }
    }

    if (!found) {
        return std::vector<Plants>{};
    }

    const std::string::size_type two = static_cast<std::string::size_type>(2U);
    const std::string::size_type one = static_cast<std::string::size_type>(1U);

    const std::string::size_type start = (index * two);

    // Bounds checks (defensive)
    if ((rows_[static_cast<std::size_t>(0U)].size() <= (start + one)) ||
        (rows_[static_cast<std::size_t>(1U)].size() <= (start + one))) {
        return std::vector<Plants>{};
    }

    const char a = rows_[static_cast<std::size_t>(0U)][start];
    const char b = rows_[static_cast<std::size_t>(0U)][(start + one)];
    const char c = rows_[static_cast<std::size_t>(1U)][start];
    const char d = rows_[static_cast<std::size_t>(1U)][(start + one)];

    std::vector<Plants> result;
    result.reserve(static_cast<std::vector<Plants>::size_type>(4U));

    try {
        result.push_back(char_to_plant(a));
        result.push_back(char_to_plant(b));
        result.push_back(char_to_plant(c));
        result.push_back(char_to_plant(d));
    } catch (const std::invalid_argument&) {
        return std::vector<Plants>{};
    }

    return result;
}

std::array<Plants, cups_per_student> plants(const std::string& diagram, const std::string& student)
{
    // Split the diagram into two rows
    const std::string::size_type newline_pos = diagram.find('\n');
    std::string row0;
    std::string row1;
    if (newline_pos == std::string::npos) {
        row0 = diagram;
        row1.clear();
    } else {
        row0 = diagram.substr(static_cast<std::string::size_type>(0U), newline_pos);
        row1 = diagram.substr((newline_pos + static_cast<std::string::size_type>(1U)));
    }

    // Find the student's index
    std::string::size_type index = static_cast<std::string::size_type>(0U);
    bool found = false;
    for (std::string::size_type i = static_cast<std::string::size_type>(0U);
         i < static_cast<std::string::size_type>(kStudents.size());
         i = (i + static_cast<std::string::size_type>(1U))) {
        if (student == std::string{kStudents[static_cast<std::size_t>(i)]}) {
            index = i;
            found = true;
            break;
        }
    }

    std::array<Plants, cups_per_student> result{};

    if (!found) {
        return result;
    }

    const std::string::size_type two = static_cast<std::string::size_type>(2U);
    const std::string::size_type one = static_cast<std::string::size_type>(1U);
    const std::string::size_type start = (index * two);

    if ((row0.size() <= (start + one)) || (row1.size() <= (start + one))) {
        return result;
    }

    const char a = row0[start];
    const char b = row0[(start + one)];
    const char c = row1[start];
    const char d = row1[(start + one)];

    try {
        result[static_cast<std::size_t>(0U)] = char_to_plant(a);
        result[static_cast<std::size_t>(1U)] = char_to_plant(b);
        result[static_cast<std::size_t>(2U)] = char_to_plant(c);
        result[static_cast<std::size_t>(3U)] = char_to_plant(d);
    } catch (const std::invalid_argument&) {
        return std::array<Plants, cups_per_student>{};
    }

    return result;
}

}  // namespace kindergarten_garden
