#pragma once
#include <vector>
#include <string>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
