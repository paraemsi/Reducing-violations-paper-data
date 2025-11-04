#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::string row0_;
    std::string row1_;

    static const std::vector<std::string>& students();
    static Plants char_to_plant(const char c);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
