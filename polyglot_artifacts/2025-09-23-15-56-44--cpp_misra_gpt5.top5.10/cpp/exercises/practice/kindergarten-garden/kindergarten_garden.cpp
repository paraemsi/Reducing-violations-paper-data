#include "kindergarten_garden.h"

#include <cstddef>
#include <stdexcept>
#include <array>
#include <utility>

namespace kindergarten_garden {

const std::vector<std::string> garden::students_{
    "Alice",   "Bob",   "Charlie", "David",
    "Eve",     "Fred",  "Ginny",   "Harriet",
    "Ileana",  "Joseph","Kincaid", "Larry"
};

plant garden::char_to_plant(char code)
{
    if (code == 'G')
    {
        return plant::grass;
    }
    else
    {
        if (code == 'C')
        {
            return plant::clover;
        }
        else
        {
            if (code == 'R')
            {
                return plant::radishes;
            }
            else
            {
                if (code == 'V')
                {
                    return plant::violets;
                }
                else
                {
                    throw std::invalid_argument("Unknown plant code");
                }
            }
        }
    }
}

garden::garden(const std::string& diagram)
    : allocations_{}
{
    const std::size_t newline_pos = diagram.find('\n');
    if (newline_pos == std::string::npos)
    {
        throw std::invalid_argument("diagram must contain exactly two rows");
    }

    const std::size_t second_newline_pos = diagram.find('\n', (newline_pos + static_cast<std::size_t>(1)));
    if (second_newline_pos != std::string::npos)
    {
        throw std::invalid_argument("diagram must contain exactly two rows");
    }

    const std::string first = diagram.substr(0U, newline_pos);
    const std::string second = diagram.substr((newline_pos + static_cast<std::size_t>(1)));

    if (first.size() != second.size())
    {
        throw std::invalid_argument("rows must be the same length");
    }
    if (((first.size() % static_cast<std::size_t>(2)) != static_cast<std::size_t>(0)))
    {
        throw std::invalid_argument("row length must be even");
    }

    for (std::size_t i = 0U; i < students_.size(); ++i)
    {
        const std::size_t pos = (i * static_cast<std::size_t>(2));
        if (((pos + static_cast<std::size_t>(1)) >= first.size()) || ((pos + static_cast<std::size_t>(1)) >= second.size()))
        {
            break;
        }

        std::vector<plant> ps;
        ps.reserve(static_cast<std::size_t>(4));

        const char a = first.at(pos);
        const char b = first.at((pos + static_cast<std::size_t>(1)));
        const char c = second.at(pos);
        const char d = second.at((pos + static_cast<std::size_t>(1)));

        ps.push_back(char_to_plant(a));
        ps.push_back(char_to_plant(b));
        ps.push_back(char_to_plant(c));
        ps.push_back(char_to_plant(d));

        allocations_.emplace(students_.at(i), std::move(ps));
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const auto it = allocations_.find(student);
    if (it != allocations_.end())
    {
        return it->second;
    }
    else
    {
        return std::vector<plant>{};
    }
}

Plants to_Plants(const plant p)
{
    switch (p)
    {
        case plant::clover:
        {
            return Plants::clover;
        }
        case plant::grass:
        {
            return Plants::grass;
        }
        case plant::radishes:
        {
            return Plants::radishes;
        }
        case plant::violets:
        {
            return Plants::violets;
        }
        default:
        {
            // Defensive default; should be unreachable
            return Plants::clover;
        }
    }
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student)
{
    const garden g(diagram);
    const std::vector<plant> vp = g.plants(student);

    std::array<Plants, 4> out{};

    std::size_t limit = static_cast<std::size_t>(4);
    if ((vp.size() < limit))
    {
        limit = vp.size();
    }

    for (std::size_t i = 0U; i < limit; ++i)
    {
        out.at(i) = to_Plants(vp.at(i));
    }

    return out;
}

}  // namespace kindergarten_garden
