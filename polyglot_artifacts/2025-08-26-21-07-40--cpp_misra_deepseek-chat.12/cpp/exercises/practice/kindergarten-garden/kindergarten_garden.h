#pragma once
#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& child);

}  // namespace kindergarten_garden
