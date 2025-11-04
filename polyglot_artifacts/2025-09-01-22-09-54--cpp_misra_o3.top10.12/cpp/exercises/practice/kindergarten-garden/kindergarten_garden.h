#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant
{
    grass,
    clover,
    radishes,
    violets
};

using Plants = plant;  // Alias preserved so tests can use kindergarten_garden::Plants

class garden
{
private:
    static const std::vector<std::string> default_students;

public:
    explicit garden(std::string_view diagram);
    garden(std::string_view diagram, std::vector<std::string> const& students);

    std::vector<plant> plants(std::string const& student) const;

private:
    std::map<std::string, std::vector<plant>> m_garden_map;

    static plant to_plant(char token);
};

std::array<Plants, 4U> plants(std::string_view diagram, std::string const& student);

}  // namespace kindergarten_garden
