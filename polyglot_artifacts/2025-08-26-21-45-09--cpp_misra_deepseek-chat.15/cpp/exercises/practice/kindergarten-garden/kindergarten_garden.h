#pragma once
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
