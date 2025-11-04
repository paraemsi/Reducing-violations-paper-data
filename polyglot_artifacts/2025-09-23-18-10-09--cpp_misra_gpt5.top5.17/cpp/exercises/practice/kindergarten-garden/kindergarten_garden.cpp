#include "kindergarten_garden.h"

#include <string>
#include <vector>
#include <array>
#include <stdexcept>
#include <cstddef>

namespace kindergarten_garden {

namespace {
    constexpr std::array<const char*, 12U> kStudents{
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
}  // namespace

garden::garden(const std::string& diagram)
{
    const std::size_t pos = diagram.find('\n');

    if ((pos == std::string::npos)) {
        throw std::invalid_argument("diagram must contain two rows separated by a newline");
    } else {
        rows_[static_cast<std::size_t>(0U)] = diagram.substr(static_cast<std::size_t>(0U), pos);
        const std::size_t start_second = (pos + static_cast<std::size_t>(1U));
        rows_[static_cast<std::size_t>(1U)] = diagram.substr(start_second);
    }

    if ((rows_[static_cast<std::size_t>(0U)].size() != rows_[static_cast<std::size_t>(1U)].size())) {
        throw std::invalid_argument("both rows must be the same length");
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const std::size_t idx = student_index(student);
    const std::size_t start = (idx * static_cast<std::size_t>(2U));

    if (
        (rows_[static_cast<std::size_t>(0U)].size() < (start + static_cast<std::size_t>(2U))) ||
        (rows_[static_cast<std::size_t>(1U)].size() < (start + static_cast<std::size_t>(2U)))
    ) {
        throw std::out_of_range("not enough cups for the requested student");
    }

    std::vector<Plants> out{};
    out.reserve(static_cast<std::size_t>(4U));

    out.push_back(char_to_plant(rows_[static_cast<std::size_t>(0U)].at(start)));
    out.push_back(char_to_plant(rows_[static_cast<std::size_t>(0U)].at(start + static_cast<std::size_t>(1U))));
    out.push_back(char_to_plant(rows_[static_cast<std::size_t>(1U)].at(start)));
    out.push_back(char_to_plant(rows_[static_cast<std::size_t>(1U)].at(start + static_cast<std::size_t>(1U))));

    return out;
}

std::size_t garden::student_index(const std::string& name)
{
    for (std::size_t i = static_cast<std::size_t>(0U); (i < kStudents.size()); ++i) {
        if ((name == kStudents[i])) {
            return i;
        }
    }
    throw std::invalid_argument("unknown student name");
}

Plants garden::char_to_plant(std::string::value_type c)
{
    if ((c == 'G')) {
        return Plants::grass;
    } else if ((c == 'C')) {
        return Plants::clover;
    } else if ((c == 'R')) {
        return Plants::radishes;
    } else if ((c == 'V')) {
        return Plants::violets;
    } else {
        throw std::invalid_argument("unknown plant code");
    }
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    const garden g(diagram);
    const std::vector<Plants> v = g.plants(student);

    std::array<Plants, 4U> result{};
    result[static_cast<std::size_t>(0U)] = v.at(static_cast<std::size_t>(0U));
    result[static_cast<std::size_t>(1U)] = v.at(static_cast<std::size_t>(1U));
    result[static_cast<std::size_t>(2U)] = v.at(static_cast<std::size_t>(2U));
    result[static_cast<std::size_t>(3U)] = v.at(static_cast<std::size_t>(3U));
    return result;
}

}  // namespace kindergarten_garden
