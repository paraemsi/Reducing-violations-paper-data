#include "kindergarten_garden.h"

#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

garden::garden(const std::string& diagram)
{
    const std::string::size_type pos = diagram.find('\n');
    if ((pos == std::string::npos))
    {
        row1_ = diagram;
        row2_.clear();
    }
    else
    {
        row1_ = diagram.substr(0U, pos);
        row2_ = diagram.substr((pos + static_cast<std::string::size_type>(1)));
    }
}

std::vector<plant> garden::plants(const std::string& student) const
{
    const std::string::size_type idx = garden::student_index(student);
    const std::string::size_type start = (idx * static_cast<std::string::size_type>(2));

    std::vector<plant> result{};
    if ((row1_.size() >= (start + static_cast<std::string::size_type>(2))) && (row2_.size() >= (start + static_cast<std::string::size_type>(2))))
    {
        const char a = row1_[start];
        const char b = row1_[(start + static_cast<std::string::size_type>(1))];
        const char c = row2_[start];
        const char d = row2_[(start + static_cast<std::string::size_type>(1))];

        result.push_back(garden::char_to_plant(a));
        result.push_back(garden::char_to_plant(b));
        result.push_back(garden::char_to_plant(c));
        result.push_back(garden::char_to_plant(d));
    }
    return result;
}

std::string::size_type garden::student_index(const std::string& student)
{
    static const std::array<std::string, 12U> names = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };

    const std::string::size_type count = static_cast<std::string::size_type>(names.size());
    for (std::string::size_type i = 0U; (i < count); ++i)
    {
        if ((student == names[i]))
        {
            return i;
        }
    }
    return static_cast<std::string::size_type>(0U);
}

plant garden::char_to_plant(const char ch)
{
    if ((ch == 'G'))
    {
        return plant::grass;
    }
    else if ((ch == 'C'))
    {
        return plant::clover;
    }
    else if ((ch == 'R'))
    {
        return plant::radishes;
    }
    else if ((ch == 'V'))
    {
        return plant::violets;
    }
    else
    {
        return plant::grass;
    }
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student)
{
    const garden g(diagram);
    const std::vector<plant> pv = g.plants(student);

    std::array<Plants, 4U> out = { plant::grass, plant::grass, plant::grass, plant::grass };
    const std::vector<plant>::size_type req = static_cast<std::vector<plant>::size_type>(4U);
    if ((pv.size() >= req))
    {
        out[0U] = pv[0U];
        out[1U] = pv[1U];
        out[2U] = pv[2U];
        out[3U] = pv[3U];
    }
    return out;
}

}  // namespace kindergarten_garden
