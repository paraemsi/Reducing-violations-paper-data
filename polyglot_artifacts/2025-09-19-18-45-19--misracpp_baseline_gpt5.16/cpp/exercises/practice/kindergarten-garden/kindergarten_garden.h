#pragma once

#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
enum class Plants { clover, grass, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
    std::vector<std::string> students_;

    static plant decode(char c);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
