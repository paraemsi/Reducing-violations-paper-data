#pragma once

#include <cstddef>
#include <cstdint>
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
using plant = Plants;
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    static const std::vector<std::string>& default_students();

    std::vector<Plants> row1_;
    std::vector<Plants> row2_;
};

}  // namespace kindergarten_garden
