#pragma once
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    clover,    // C
    grass,     // G
    radishes,  // R
    violets    // V
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
