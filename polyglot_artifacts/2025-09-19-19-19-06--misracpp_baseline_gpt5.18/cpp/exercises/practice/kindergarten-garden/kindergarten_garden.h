#pragma once

#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    std::vector<std::string> students_;
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
