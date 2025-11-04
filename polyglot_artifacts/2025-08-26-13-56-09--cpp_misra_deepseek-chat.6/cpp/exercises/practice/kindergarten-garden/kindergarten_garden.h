#pragma once
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

std::vector<Plants> plants(const std::string& diagram, const std::string& child);

}  // namespace kindergarten_garden
