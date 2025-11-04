#pragma once

#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plant {
    grass,
    clover,
    radishes,
    violets
};

std::vector<Plant> plants(const std::string& diagram, const std::string& child);

}  // namespace kindergarten_garden
