#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>

namespace kindergarten_garden {

namespace
{
    // Helper to alphabetically sort a copy of the provided student list.
    [[nodiscard]] std::vector<std::string> sort_students(const std::vector<std::string>& names)
    {
        auto copy = names;
        std::sort(copy.begin(), copy.end());
        return copy;
    }
}  // unnamed namespace

plant garden::char_to_plant(char c)
{
    if ((c == 'G'))
    {
        return plant::grass;
    }
    else if ((c == 'C'))
    {
        return plant::clover;
    }
    else if ((c == 'R'))
    {
        return plant::radishes;
    }
    else if ((c == 'V'))
    {
        return plant::violets;
    }
    else
    {
        throw std::invalid_argument("Invalid plant code");
    }
}

garden::garden(const std::string& diagram, const std::vector<std::string>& students_in)
{
    std::vector<std::string> students{};

    if (students_in.empty())
    {
        students.assign(default_students_.begin(), default_students_.end());
    }
    else
    {
        students = sort_students(students_in);
    }

    const std::string::size_type newline_pos{diagram.find('\n')};

    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    const std::string row1{diagram.substr(0U, newline_pos)};
    const std::string row2{diagram.substr(newline_pos + 1U)};

    const std::size_t expected_length{students.size() * static_cast<std::size_t>(2U)};

    if ((row1.length() != expected_length) || (row2.length() != expected_length))
    {
        throw std::invalid_argument("Row length mismatch");
    }

    for (std::size_t i{0U}; i < students.size(); ++i)
    {
        const std::size_t base_idx{static_cast<std::size_t>(2U) * i};

        std::vector<plant> p{};
        p.reserve(4U);

        p.push_back(char_to_plant(row1[base_idx]));
        p.push_back(char_to_plant(row1[base_idx + static_cast<std::size_t>(1U)]));
        p.push_back(char_to_plant(row2[base_idx]));
        p.push_back(char_to_plant(row2[base_idx + static_cast<std::size_t>(1U)]));

        lookup_.emplace(students[i], p);
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it{lookup_.find(student)};
    if (it == lookup_.end())
    {
        return {};
    }
    return it->second;
}

/*------------------------------------------------------------
 * Free-function wrapper – converts the vector returned by the
 * garden helper into the fixed-size std::array requested by
 * the unit tests.
 *----------------------------------------------------------*/
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students_in)
{
    const garden g(diagram, students_in);
    const std::vector<plant> vec{g.plants(student)};

    /*  The exercise guarantees exactly four plants per student,
     *  but defend anyway – return an empty array if not.
     */
    if (vec.size() != static_cast<std::size_t>(4U))
    {
        return {};
    }

    return {vec[0], vec[1], vec[2], vec[3]};
}

}  // namespace kindergarten_garden
