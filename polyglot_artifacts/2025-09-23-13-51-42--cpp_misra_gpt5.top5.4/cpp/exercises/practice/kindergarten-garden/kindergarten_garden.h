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

enum class Plants : std::uint8_t {
    clover,
    grass,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
