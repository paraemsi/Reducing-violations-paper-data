#pragma once

#include <array>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant
{
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden
{
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> students_{};

    std::array<std::string, 2U> rows_{};

    static plant char_to_plant(const char c);
};

}  // namespace kindergarten_garden
