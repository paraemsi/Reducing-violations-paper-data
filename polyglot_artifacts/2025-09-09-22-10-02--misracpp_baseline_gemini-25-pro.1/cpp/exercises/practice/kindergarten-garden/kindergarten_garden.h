#pragma once

#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    violets,
    clover,
    radishes,
    grass,
};

std::vector<Plants> plants(const std::string& diagram, const std::string& name);

}  // namespace kindergarten_garden
