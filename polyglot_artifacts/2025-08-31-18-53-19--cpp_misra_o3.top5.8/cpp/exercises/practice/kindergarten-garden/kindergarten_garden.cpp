#include "kindergarten_garden.h"

#include <algorithm>
#include <stdexcept>

namespace kindergarten_garden {

namespace {

/*  Default list of students in alphabetical order, as specified. */
static const std::array<std::string, 12U> default_students{
    "Alice",   "Bob",    "Charlie", "David",
    "Eve",     "Fred",   "Ginny",   "Harriet",
    "Ileana",  "Joseph", "Kincaid", "Larry"};

}  // namespace

/*  Helper to convert a character code into the corresponding plant. */
Plants garden::char_to_plant(char code)
{
    switch (code) {
        case 'G':
            return Plants::grass;
        case 'C':
            return Plants::clover;
        case 'R':
            return Plants::radishes;
        case 'V':
            return Plants::violets;
        default:
            throw std::invalid_argument("Invalid plant code in diagram");
    }
}

/*  Constructor splits the two diagram rows. */
garden::garden(const std::string& diagram)
    : students_{default_students.cbegin(), default_students.cend()}
{
    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    rows_[0U] = diagram.substr(0U, newline_pos);
    rows_[1U] = diagram.substr(newline_pos + 1U);

    /*  Basic validation: both rows must have the same even length
        (two cups per child). */
    if ((rows_[0U].length() != rows_[1U].length()) ||
        ((rows_[0U].length() % 2U) != 0U)) {
        throw std::invalid_argument("Rows must be of equal even length");
    }
}

/*  Retrieve the four plants assigned to the named student. */
std::array<Plants, 4U> garden::plants(const std::string& student) const
{
    const auto it{std::find(students_.cbegin(), students_.cend(), student)};
    if (it == students_.cend()) {
        throw std::invalid_argument("Unknown student");
    }

    const std::size_t index{
        static_cast<std::size_t>(std::distance(students_.cbegin(), it))};

    const std::size_t start{index * 2U};

    std::array<Plants, 4U> result{{
        char_to_plant(rows_[0U][start]),
        char_to_plant(rows_[0U][start + 1U]),
        char_to_plant(rows_[1U][start]),
        char_to_plant(rows_[1U][start + 1U])}};

    return result;
}

/*  Constructor that accepts a custom list of students. */
garden::garden(const std::string& diagram, const std::vector<std::string>& students)
    : students_{students}
{
    /*  Sort the supplied student names alphabetically. */
    std::sort(students_.begin(), students_.end());

    const std::size_t newline_pos{diagram.find('\n')};
    if (newline_pos == std::string::npos) {
        throw std::invalid_argument("Diagram must contain two rows");
    }

    rows_[0U] = diagram.substr(0U, newline_pos);
    rows_[1U] = diagram.substr(newline_pos + 1U);

    if ((rows_[0U].length() != rows_[1U].length()) ||
        ((rows_[0U].length() % 2U) != 0U)) {
        throw std::invalid_argument("Rows must be of equal even length");
    }
}

/*  Free function wrapper required by the tests. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g(diagram);
    return g.plants(student);
}

}  // namespace kindergarten_garden
