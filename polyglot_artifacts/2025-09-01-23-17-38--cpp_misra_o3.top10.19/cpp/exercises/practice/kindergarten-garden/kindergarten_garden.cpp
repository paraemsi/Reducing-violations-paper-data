#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace kindergarten_garden {

/* Initialise the static list of default children. */
const std::array<std::string, 12U> garden::default_children{
    "Alice",  "Bob",  "Charlie", "David",   "Eve",  "Fred",
    "Ginny",  "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};

/* Helper translating a single character to its corresponding plant enum. */
plant symbol_to_plant(char symbol)
{
    /* Equality comparison on same character type is allowed. */
    switch (symbol)
    {
        case 'C':
            return plant::clover;
        case 'G':
            return plant::grass;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            throw std::invalid_argument("Invalid plant symbol in diagram.");
    }
}

/* Constructor splits the diagram into the two logical rows. */
garden::garden(const std::string& diagram, std::vector<std::string> children)
    : m_children(std::move(children))
{
    if (m_children.empty())
    {
        m_children.assign(default_children.begin(), default_children.end());
    }
    auto const newline_pos{diagram.find('\n')};

    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain a newline separating rows.");
    }

    m_row1 = diagram.substr(0U, newline_pos);
    m_row2 = diagram.substr(newline_pos + 1U);

    /* Each row must contain exactly two cups per child. */
    if ((m_row1.length() != m_row2.length()) ||
        ((m_row1.length() % 2U) != 0U) ||
        ((m_row1.length() / 2U) != m_children.size()))
    {
        throw std::invalid_argument("Diagram dimensions do not match child count.");
    }

    /* Ensure children are sorted alphabetically to fulfil the assignment rule. */
    std::sort(m_children.begin(), m_children.end());
}

/* Return the four plants belonging to the requested child. */
std::vector<plant> garden::plants(const std::string& child) const
{
    auto const it{std::find(m_children.begin(), m_children.end(), child)};

    if (it == m_children.end())
    {
        throw std::invalid_argument("Unknown child.");
    }

    std::size_t const index{static_cast<std::size_t>(std::distance(m_children.begin(), it))};
    std::size_t const offset{index * 2U};

    /* Collect the two cups from each row. */
    std::vector<plant> result;
    result.reserve(4U);

    result.push_back(symbol_to_plant(m_row1[offset]));
    result.push_back(symbol_to_plant(m_row1[offset + 1U]));
    result.push_back(symbol_to_plant(m_row2[offset]));
    result.push_back(symbol_to_plant(m_row2[offset + 1U]));

    return result;
}

/* Convenience free function mirroring the expectations of the unit tests. */
std::array<plant, 4U> plants(const std::string& diagram,
                             const std::string& child,
                             std::vector<std::string> children)
{
    garden g(diagram, std::move(children));
    auto const vec{g.plants(child)};

    /* vec is guaranteed by garden::plants to contain exactly four entries. */
    std::array<plant, 4U> result{};
    result[0U] = vec[0U];
    result[1U] = vec[1U];
    result[2U] = vec[2U];
    result[3U] = vec[3U];

    return result;
}

}  // namespace kindergarten_garden
