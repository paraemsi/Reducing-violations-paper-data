#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row0_;
    std::string row1_;
};

}  // namespace kindergarten_garden
