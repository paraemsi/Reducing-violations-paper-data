#pragma once

#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    grass,
    clover,
    radishes,
    violets
};

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
};

}  // namespace kindergarten_garden
