#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using child_index_t = std::uint8_t;

enum class Plants
{
    grass,
    clover,
    radishes,
    violets
}; // MISRA C++: add semicolon after enum class

std::vector<Plants> plants(const std::string& diagram, const std::string& child_name);

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& child_name) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> children_;
    static child_index_t child_index(const std::string& child_name);
    static Plants decode_plant(char code);
};

}  // namespace kindergarten_garden
