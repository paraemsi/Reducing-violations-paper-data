#include "kindergarten_garden.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

static constexpr std::string::size_type cups_per_student = static_cast<std::string::size_type>(2U);

const std::vector<std::string>& garden::students_order()
{
    static const std::vector<std::string> order = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    return order;
}

plant garden::to_plant(std::string::value_type code)
{
    if ((code == 'G')) {
        return plant::grass;
    } else if ((code == 'C')) {
        return plant::clover;
    } else if ((code == 'R')) {
        return plant::radishes;
    } else if ((code == 'V')) {
        return plant::violets;
    } else {
        // Treat any other valid diagram code as violets
        return plant::violets;
    }
}

garden::garden(const std::string& diagram)
    : m_row1(), m_row2()
{
    const std::string::size_type newline = diagram.find('\n');
    if ((newline == std::string::npos)) {
        m_row1 = diagram;
        m_row2 = std::string();
    } else {
        m_row1 = diagram.substr(static_cast<std::string::size_type>(0U), newline);
        m_row2 = diagram.substr((newline + static_cast<std::string::size_type>(1U)));
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const std::vector<std::string>& order = students_order();

    bool found = false;
    std::vector<std::string>::size_type idx = static_cast<std::vector<std::string>::size_type>(0U);
    for (std::vector<std::string>::size_type i = static_cast<std::vector<std::string>::size_type>(0U); (i < order.size()); ++i) {
        if (order[i] == student) {
            idx = i;
            found = true;
            break;
        }
    }

    if (!found) {
        return std::vector<plant>();
    } else {
        const std::string::size_type pos_index = static_cast<std::string::size_type>(idx);
        const std::string::size_type offset = (pos_index * cups_per_student);

        std::vector<plant> result;
        result.reserve(static_cast<std::vector<plant>::size_type>(4U));

        if ((offset < m_row1.size()) && ((offset + static_cast<std::string::size_type>(1U)) < m_row1.size())) {
            result.push_back(to_plant(m_row1[offset]));
            result.push_back(to_plant(m_row1[(offset + static_cast<std::string::size_type>(1U))]));
        }

        if ((offset < m_row2.size()) && ((offset + static_cast<std::string::size_type>(1U)) < m_row2.size())) {
            result.push_back(to_plant(m_row2[offset]));
            result.push_back(to_plant(m_row2[(offset + static_cast<std::string::size_type>(1U))]));
        }

        return result;
    }
}

static Plants to_Plants(plant p) // NOLINT(readability-identifier-naming)
{
    switch (p) {
        case plant::clover:
            return Plants::clover;
        case plant::grass:
            return Plants::grass;
        case plant::radishes:
            return Plants::radishes;
        case plant::violets:
            return Plants::violets;
        default:
            return Plants::clover;
    }
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student)
{
    garden g(diagram);
    const std::vector<plant> v = g.plants(student);

    std::array<Plants, 4> out = {
        Plants::clover, Plants::clover, Plants::clover, Plants::clover
    };

    std::array<Plants, 4>::size_type n = static_cast<std::array<Plants, 4>::size_type>(v.size());
    if (n > static_cast<std::array<Plants, 4>::size_type>(out.size())) {
        n = static_cast<std::array<Plants, 4>::size_type>(out.size());
    }

    for (std::array<Plants, 4>::size_type i = static_cast<std::array<Plants, 4>::size_type>(0U); (i < n); ++i) {
        out[i] = to_Plants(v[i]);
    }

    return out;
}

}  // namespace kindergarten_garden
