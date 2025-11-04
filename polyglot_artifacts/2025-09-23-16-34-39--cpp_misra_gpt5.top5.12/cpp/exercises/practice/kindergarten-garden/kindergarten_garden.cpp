#include "kindergarten_garden.h"

namespace kindergarten_garden {

garden::garden(const std::string& diagram)
{
    const std::size_t pos = diagram.find('\n');
    if (pos == std::string::npos) {
        rows_[0] = diagram;
        rows_[1].clear();
    } else {
        rows_[0] = diagram.substr(0U, pos);
        rows_[1] = diagram.substr((pos + 1U));
    }
}

std::vector<plant> garden::plants(const std::string& name) const
{
    const std::size_t idx = garden::student_index(name);
    constexpr std::size_t cups_per_student{2U};
    const std::size_t start = (idx * cups_per_student);

    std::vector<plant> result{};
    result.reserve(4U);

    if ((rows_[0].size() >= (start + 2U))) {
        result.push_back(garden::decode(rows_[0][start]));
        result.push_back(garden::decode(rows_[0][(start + 1U)]));
    } else if ((rows_[0].size() >= (start + 1U))) {
        result.push_back(garden::decode(rows_[0][start]));
    } else {
        // no cups in first row for this index
    }

    if ((rows_[1].size() >= (start + 2U))) {
        result.push_back(garden::decode(rows_[1][start]));
        result.push_back(garden::decode(rows_[1][(start + 1U)]));
    } else if ((rows_[1].size() >= (start + 1U))) {
        result.push_back(garden::decode(rows_[1][start]));
    } else {
        // no cups in second row for this index
    }

    return result;
}

std::size_t garden::student_index(const std::string& name) noexcept
{
    // Alphabetical order as specified.
    constexpr std::size_t count{12U};
    const std::array<std::string, count> names{
        std::string("Alice"),
        std::string("Bob"),
        std::string("Charlie"),
        std::string("David"),
        std::string("Eve"),
        std::string("Fred"),
        std::string("Ginny"),
        std::string("Harriet"),
        std::string("Ileana"),
        std::string("Joseph"),
        std::string("Kincaid"),
        std::string("Larry")
    };

    for (std::size_t i{0U}; (i < names.size()); ++i) {
        if ((names[i] == name)) {
            return i;
        } else {
            // continue searching
        }
    }

    // Default to Alice if name not found (defensive fallback).
    return 0U;
}

plant garden::decode(const char c) noexcept
{
    if ((c == 'G')) {
        return plant::grass;
    } else if ((c == 'C')) {
        return plant::clover;
    } else if ((c == 'R')) {
        return plant::radishes;
    } else if ((c == 'V')) {
        return plant::violets;
    } else {
        // Unknown plant code; default defensively.
        return plant::grass;
    }
}


std::array<Plants, 4> plants(const std::string& diagram, const std::string& name) noexcept
{
    garden g(diagram);
    const std::vector<plant> v = g.plants(name);

    std::array<Plants, 4> out{
        Plants::grass, Plants::grass, Plants::grass, Plants::grass
    };

    for (std::size_t i{0U}; ((i < v.size()) && (i < 4U)); ++i) {
        out[i] = to_Plants(v[i]);
    }

    return out;
}

}  // namespace kindergarten_garden
