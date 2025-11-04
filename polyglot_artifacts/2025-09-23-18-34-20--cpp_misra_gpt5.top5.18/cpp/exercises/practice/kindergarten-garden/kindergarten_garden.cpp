#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

namespace {
    Plants to_plant(const char code)
    {
        switch (code) {
            case 'C':
            {
                return Plants::clover;
            }
            case 'G':
            {
                return Plants::grass;
            }
            case 'R':
            {
                return Plants::radishes;
            }
            case 'V':
            {
                return Plants::violets;
            }
            default:
            {
                throw std::invalid_argument("Unknown plant code");
            }
        }
    }
}  // namespace

const std::vector<std::string>& garden::default_students()
{
    static const std::vector<std::string> names = {
        "Alice",  "Bob",   "Charlie", "David",
        "Eve",    "Fred",  "Ginny",   "Harriet",
        "Ileana", "Joseph","Kincaid", "Larry"
    };
    return names;
}

garden::garden(const std::string& diagram)
{
    const std::string::size_type newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    } else {
        const std::string first = diagram.substr(0U, newline_pos);
        const std::string second = diagram.substr((newline_pos + static_cast<std::string::size_type>(1U)));

        if (first.size() != second.size()) {
            throw std::invalid_argument("Diagram rows must be the same length");
        }
        if ((first.size() % static_cast<std::string::size_type>(2U)) != static_cast<std::string::size_type>(0U)) {
            throw std::invalid_argument("Each row must have an even number of cups");
        }

        row1_.reserve(first.size());
        for (const char ch : first) {
            row1_.push_back(to_plant(ch));
        }

        row2_.reserve(second.size());
        for (const char ch : second) {
            row2_.push_back(to_plant(ch));
        }
    }
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const std::vector<std::string>& names = default_students();

    std::size_t idx = 0U;
    for (const std::string& name : names) {
        if (name == student) {
            break;
        } else {
            idx = (idx + static_cast<std::size_t>(1U));
        }
    }

    if (idx == names.size()) {
        return std::vector<Plants>{};
    }

    const std::size_t pos = (static_cast<std::size_t>(2U) * idx);

    std::vector<Plants> result;
    result.reserve(static_cast<std::size_t>(4U));

    if ((pos + static_cast<std::size_t>(1U)) < row1_.size()) {
        result.push_back(row1_[pos]);
        result.push_back(row1_[(pos + static_cast<std::size_t>(1U))]);
    }
    if ((pos + static_cast<std::size_t>(1U)) < row2_.size()) {
        result.push_back(row2_[pos]);
        result.push_back(row2_[(pos + static_cast<std::size_t>(1U))]);
    }

    return result;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    const std::vector<Plants> v = g.plants(student);

    std::array<Plants, 4> out = {Plants::clover, Plants::clover, Plants::clover, Plants::clover};

    if (v.size() >= static_cast<std::size_t>(4U)) {
        out[0U] = v[0U];
        out[1U] = v[1U];
        out[2U] = v[2U];
        out[3U] = v[3U];
    } else {
        if (v.size() > static_cast<std::size_t>(0U)) { out[0U] = v[0U]; }
        if (v.size() > static_cast<std::size_t>(1U)) { out[1U] = v[1U]; }
        if (v.size() > static_cast<std::size_t>(2U)) { out[2U] = v[2U]; }
        if (v.size() > static_cast<std::size_t>(3U)) { out[3U] = v[3U]; }
    }

    return out;
}

}  // namespace kindergarten_garden
