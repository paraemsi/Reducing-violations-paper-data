#pragma once
#include <vector>
#include <string>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
