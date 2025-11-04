#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
