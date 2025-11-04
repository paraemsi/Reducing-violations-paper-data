#include "kindergarten_garden.h"

#include <algorithm>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

/* Initialise the default student list once, in alphabetical order */
const std::vector<std::string> default_student_names =
{
    "Alice",  "Bob",    "Charlie", "David",
    "Eve",    "Fred",   "Ginny",   "Harriet",
    "Ileana", "Joseph", "Kincaid", "Larry"
};

garden::garden(const std::string& diagram, const std::vector<std::string>& students)
{
    /* The diagram must contain exactly two rows separated by a newline */
    const std::string::size_type newline_pos{diagram.find('\n')};

    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("Diagram must contain exactly two rows separated by a newline.");
    }

    const std::string row1{diagram.substr(0U, newline_pos)};
    const std::string row2{diagram.substr(newline_pos + 1U)};

    if (row1.length() != row2.length())
    {
        throw std::invalid_argument("Both diagram rows must be of equal length.");
    }

    /* Each student receives two cups per row, thus rows must contain an even count of cups */
    if ((row1.length() % 2U) != 0U)
    {
        throw std::invalid_argument("Each row must contain an even number of plant codes.");
    }

    std::vector<std::string> roster{students};
    std::sort(roster.begin(), roster.end());

    /* Verify that the diagram provides enough cups for every student */
    if ((row1.length() / 2U) < roster.size())
    {
        throw std::invalid_argument("Not enough cups for the supplied list of students.");
    }

    for (std::size_t student_index{0U}; student_index < roster.size(); ++student_index)
    {
        const std::string& name{roster[student_index]};
        const std::size_t   column{student_index * 2U};

        std::array<Plants, 4> cups{
            char_to_plant(row1[column]),
            char_to_plant(row1[column + 1U]),
            char_to_plant(row2[column]),
            char_to_plant(row2[column + 1U])};

        assignments_.insert({name, cups});
    }
}

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student)
{
    const garden g(diagram, default_student_names);
    return g.plants(student);
}

Plants garden::char_to_plant(char input)
{
    if ((input == 'G'))
    {
        return Plants::grass;
    }
    else if ((input == 'C'))
    {
        return Plants::clover;
    }
    else if ((input == 'R'))
    {
        return Plants::radishes;
    }
    else if ((input == 'V'))
    {
        return Plants::violets;
    }
    else
    {
        throw std::invalid_argument("Invalid plant code found in diagram.");
    }
}

std::array<Plants, 4> garden::plants(const std::string& student) const
{
    const auto it{assignments_.find(student)};

    if (it == assignments_.end())
    {
        throw std::out_of_range("Student name not found in this garden.");
    }

    return it->second;
}

}  // namespace kindergarten_garden
