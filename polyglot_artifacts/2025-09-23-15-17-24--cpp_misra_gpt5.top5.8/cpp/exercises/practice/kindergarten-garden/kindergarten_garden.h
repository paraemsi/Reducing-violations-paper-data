#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant : std::uint8_t {
    clover,
    grass,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student_name) const;

private:
    std::array<std::string, 2U> rows_{};
};

using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student_name);

}  // namespace kindergarten_garden
