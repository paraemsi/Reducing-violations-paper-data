#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace kindergarten_garden {

/*  Enumeration of the possible plants found in the cups. */
enum class Plants
{
    clover,
    grass,
    radishes,
    violets
};

/*  The garden class assigns plants to each student as dictated by the diagram. */
class garden
{
public:
    explicit garden(const std::string &diagram);
    garden(const std::string &diagram, const std::vector<std::string> &students);

    std::vector<Plants> plants(const std::string &student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> m_assignments;

    static Plants char_to_plant(char symbol);
    static std::vector<std::string> default_students();
    static constexpr std::size_t cups_per_student() noexcept
    {
        return static_cast<std::size_t>(4U);
    }
};

/*  Free helper demanded by the tests – returns the four plants for one student. */
std::array<Plants, 4U> plants(const std::string &diagram, const std::string &student);

}  // namespace kindergarten_garden
