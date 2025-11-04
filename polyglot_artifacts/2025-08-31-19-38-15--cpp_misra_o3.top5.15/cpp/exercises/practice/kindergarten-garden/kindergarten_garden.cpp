#include "kindergarten_garden.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <array>

namespace kindergarten_garden {

/* Convert the diagram character to a plant enum value. */
static plant char_to_plant(char c)
{
    /* Use explicit equality comparisons to avoid relying on the
       underlying numeric value of the character, as required by MISRA. */
    if (c == 'G')
    {
        return plant::grass;
    }
    if (c == 'C')
    {
        return plant::clover;
    }
    if (c == 'R')
    {
        return plant::radishes;
    }
    if (c == 'V')
    {
        return plant::violets;
    }
    throw std::invalid_argument("invalid plant code");
}

/* Default alphabetical roster. */
std::vector<std::string> garden::default_students()
{
    return { "Alice",   "Bob",  "Charlie", "David",
             "Eve",     "Fred", "Ginny",   "Harriet",
             "Ileana",  "Joseph", "Kincaid", "Larry" };
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    /* Split the diagram into its two rows. */
    std::istringstream iss(diagram);
    std::string row1;
    std::string row2;
    std::getline(iss, row1);
    /* Skip any leading empty line that may precede the diagram. */
    if (row1.empty())
    {
        std::getline(iss, row1);
    }
    std::getline(iss, row2);

    if ((row1.length() != row2.length()) ||
        ((row1.length() % 2U) != 0U))
    {
        throw std::invalid_argument("diagram rows must be equal length and even");
    }

    /* Use the provided roster order verbatim (do not sort). */
    const index_t child_count = static_cast<index_t>(students.size());
    const index_t expected_cups =
        static_cast<index_t>(row1.length());

    if ((child_count * 2U) != expected_cups)
    {
        throw std::invalid_argument("student count does not match diagram");
    }

    /* Assign plants to each child. */
    for (index_t i = static_cast<index_t>(0); i < child_count; ++i)
    {
        const index_t pos = static_cast<index_t>(i * 2U);

        std::vector<plant> child_plants;
        child_plants.reserve(4U);
        child_plants.push_back(
            char_to_plant(row1[static_cast<std::size_t>(pos)]));
        child_plants.push_back(
            char_to_plant(row1[static_cast<std::size_t>(pos + static_cast<index_t>(1))]));
        child_plants.push_back(
            char_to_plant(row2[static_cast<std::size_t>(pos)]));
        child_plants.push_back(
            char_to_plant(row2[static_cast<std::size_t>(pos + static_cast<index_t>(1))]));

        m_assignments.insert(
            { students[static_cast<std::size_t>(i)], child_plants });
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it = m_assignments.find(student);
    if (it == m_assignments.end())
    {
        return {};
    }
    return it->second;
}

/* Public helper mandated by the exercise test-suite. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students)
{
    const garden g(diagram, students);

    const std::vector<plant> vec = g.plants(student);
    if (vec.size() != static_cast<std::size_t>(4U))
    {
        throw std::invalid_argument("student does not have exactly 4 plants");
    }

    std::array<Plants, 4U> result{};
    for (std::size_t i = static_cast<std::size_t>(0); i < static_cast<std::size_t>(4U); ++i)
    {
        result[i] = vec[i]; /* `Plants` is an alias of `plant`              */
    }
    return result;
}

}  // namespace kindergarten_garden
