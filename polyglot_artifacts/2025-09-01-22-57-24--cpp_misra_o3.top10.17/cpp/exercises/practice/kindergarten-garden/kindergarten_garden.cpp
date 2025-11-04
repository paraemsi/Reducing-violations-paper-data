#include "kindergarten_garden.h"
#include <utility>
#include <array>

namespace kindergarten_garden {

namespace
{
    /*  Split the diagram into its two constituent rows. */
    std::pair<std::string, std::string> split_rows(const std::string &diagram)
    {
        /*  Remove an optional leading or trailing newline so that exactly one
            newline remains – the separator between the two rows. */
        std::string trimmed{diagram};

        if((!trimmed.empty()) && (trimmed.front() == '\n'))
        {
            trimmed.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
        }

        if((!trimmed.empty()) && (trimmed.back() == '\n'))
        {
            trimmed.pop_back();
        }

        const std::size_t newline_pos{trimmed.find('\n')};

        if(newline_pos == std::string::npos)
        {
            throw std::invalid_argument("diagram must contain a newline separating two rows");
        }

        const std::string row_first{trimmed.substr(static_cast<std::size_t>(0U), newline_pos)};
        const std::string row_second{
            trimmed.substr(newline_pos + static_cast<std::size_t>(1U))};

        return std::make_pair(row_first, row_second);
    }
}  // unnamed namespace

garden::garden(const std::string &diagram) : garden(diagram, default_students())
{
}

garden::garden(const std::string &diagram, const std::vector<std::string> &students)
{
    const auto rows{split_rows(diagram)};

    std::vector<std::string> sorted_students{students};
    std::sort(sorted_students.begin(), sorted_students.end());

    const std::size_t expected_length{static_cast<std::size_t>(sorted_students.size()) *
                                      static_cast<std::size_t>(2U)};

    if((rows.first.length() != expected_length) || (rows.second.length() != expected_length))
    {
        throw std::invalid_argument("diagram row length does not match number of students");
    }

    for(std::size_t idx{0U}; idx < sorted_students.size(); ++idx)
    {
        const std::size_t start{idx * static_cast<std::size_t>(2U)};

        std::vector<Plants> child_plants;
        child_plants.reserve(cups_per_student());

        child_plants.emplace_back(char_to_plant(rows.first[start]));
        child_plants.emplace_back(char_to_plant(rows.first[start + static_cast<std::size_t>(1U)]));
        child_plants.emplace_back(char_to_plant(rows.second[start]));
        child_plants.emplace_back(char_to_plant(rows.second[start + static_cast<std::size_t>(1U)]));

        m_assignments.emplace(sorted_students[idx], std::move(child_plants));
    }
}

std::vector<Plants> garden::plants(const std::string &student) const
{
    const auto it{m_assignments.find(student)};

    if(it == m_assignments.end())
    {
        return {};
    }

    return it->second;
}

Plants garden::char_to_plant(char symbol)
{
    switch(symbol)
    {
        case 'G':
            return plant::grass;
        case 'C':
            return plant::clover;
        case 'R':
            return plant::radishes;
        case 'V':
            return plant::violets;
        default:
            throw std::invalid_argument("unknown plant code");
    }
}

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

/*  Free helper – builds a temporary garden and returns the four plants for
    the requested student, as required by the test harness. */
std::array<Plants, 4U> plants(const std::string &diagram, const std::string &student)
{
    const garden g(diagram);
    const std::vector<Plants> vec{g.plants(student)};

    std::array<Plants, 4U> result{};
    std::copy(vec.begin(), vec.end(), result.begin());
    return result;
}

}  // namespace kindergarten_garden
