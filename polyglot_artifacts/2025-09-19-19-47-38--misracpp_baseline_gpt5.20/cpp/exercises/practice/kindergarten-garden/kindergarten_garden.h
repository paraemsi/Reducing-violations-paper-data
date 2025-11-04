#pragma once

#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, std::vector<std::string> students);
    std::vector<plant> plants(const std::string& student) const;

private:
    static plant char_to_plant(char c);
    std::vector<std::string> roster_;
    std::string row1_;
    std::string row2_;
};

}  // namespace kindergarten_garden
