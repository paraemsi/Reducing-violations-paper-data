#include "kindergarten_garden.h"

#include <array>
#include <stdexcept>

namespace kindergarten_garden {

namespace
{
    constexpr char row_delim = '\n';
}  // unnamed namespace

garden::garden(const std::string& diagram,
               const std::vector<std::string>& students)
{
    const std::string::size_type pos = diagram.find(row_delim);
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("diagram must contain two rows");
    }

    const std::string row1 = diagram.substr(0U, pos);
    std::string row2 = diagram.substr(pos + static_cast<std::string::size_type>(1U));
    /* Trim any trailing newline characters so that the second row length
     * strictly reflects the number of cups.  An equality comparison on
     * character operands is permissible under the project rules. */
    while ((!row2.empty()) && (row2.back() == row_delim))
    {
        row2.pop_back();
    }

    std::vector<std::string> roster = students;
    if (roster.empty())
    {
        roster = {"Alice",   "Bob",  "Charlie", "David",
                  "Eve",     "Fred", "Ginny",   "Harriet",
                  "Ileana", "Joseph", "Kincaid", "Larry"};
    }
    std::sort(roster.begin(), roster.end());

    const index_t cup_count = static_cast<index_t>(row1.length());
    if ((cup_count != row2.length()) ||
        ((cup_count % static_cast<index_t>(2U)) != static_cast<index_t>(0U)) ||
        (cup_count != (static_cast<index_t>(roster.size()) * static_cast<index_t>(2U))))
    {
        throw std::invalid_argument("diagram rows do not match roster");
    }

    for (index_t i = 0U; i < static_cast<index_t>(roster.size()); ++i)
    {
        const index_t offset = (static_cast<index_t>(2U) * i);

        std::vector<Plants> cups;
        cups.reserve(4U);

        cups.push_back(decodePlant(row1[offset]));
        cups.push_back(decodePlant(row1[offset + static_cast<index_t>(1U)]));
        cups.push_back(decodePlant(row2[offset]));
        cups.push_back(decodePlant(row2[offset + static_cast<index_t>(1U)]));

        assignments_.emplace(roster[i], cups);
    }
}

Plants garden::decodePlant(char code)
{
    if (code == 'G')
    {
        return Plants::grass;
    }
    else if (code == 'C')
    {
        return Plants::clover;
    }
    else if (code == 'R')
    {
        return Plants::radishes;
    }
    else if (code == 'V')
    {
        return Plants::violets;
    }
    throw std::invalid_argument("unknown plant code");
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it = assignments_.find(student);
    if (it == assignments_.end())
    {
        throw std::out_of_range("student not found");
    }
    return it->second;
}

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    const garden g(diagram);
    const std::vector<Plants> vec = g.plants(student);

    std::array<Plants, 4U> arr{};
    for (std::size_t i = 0U; i < static_cast<std::size_t>(4U); ++i)
    {
        arr[i] = vec[i];
    }
    return arr;
}

}  // namespace kindergarten_garden
