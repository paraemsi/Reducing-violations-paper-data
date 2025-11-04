#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

/* Convert the single-letter code from the diagram into the corresponding
 * strongly-typed enumeration value. */
Plants garden::char_to_plant(const char c)
{
    /* Equality comparison on character operands is allowed by the rules. */
    switch (c)
    {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            /* An invalid character in the diagram – signal a logic error. */
            throw std::invalid_argument("Invalid plant code in diagram");
    }
}

/* The default alphabetical roster dictated by the specification. */
std::vector<std::string> garden::default_students()
{
    return {"Alice",
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
            "Larry"};
}

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    /* The diagram must contain exactly two rows separated by a single '\n'. */
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    const std::string row1{diagram.substr(0U, newline_pos)};
    const std::string row2{diagram.substr(newline_pos + 1U)};

    if (row1.length() != row2.length())
    {
        throw std::invalid_argument("Rows must be of equal length");
    }

    /* Each student owns two cups per row.  Validate that the diagram width
     * matches the student count. */
    const std::size_t expected_width{static_cast<std::size_t>(students.size()) * 2U};
    if (row1.length() != expected_width)
    {
        throw std::invalid_argument("Diagram width does not match student count");
    }

    /* Build a sorted copy of the roster so that cup assignment follows the
     * required alphabetical order irrespective of the caller’s input order. */
    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    /* Assign the four plants to each student. */
    for (std::size_t i{0U}; i < sorted_students.size(); ++i)
    {
        const std::size_t start_idx{static_cast<std::size_t>(i) * 2U};

        std::array<Plants, 4U> allocation{
            char_to_plant(row1[start_idx]),
            char_to_plant(row1[start_idx + 1U]),
            char_to_plant(row2[start_idx]),
            char_to_plant(row2[start_idx + 1U])};

        assignments_.emplace(sorted_students[i], allocation);
    }
}

std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    const auto it{assignments_.find(student)};
    if (it == assignments_.end())
    {
        throw std::out_of_range("Student not found in the garden");
    }

    return it->second;
}

/* Free function wrapper expected by the test suite. */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    const garden g{diagram};
    return g.plants(student);
}

}  // namespace kindergarten_garden
