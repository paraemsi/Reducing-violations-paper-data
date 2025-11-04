#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

enum class Plants {
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
    static const std::vector<std::string> students_;
    std::unordered_map<std::string, std::vector<plant>> allocations_;
    static plant char_to_plant(char code);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
