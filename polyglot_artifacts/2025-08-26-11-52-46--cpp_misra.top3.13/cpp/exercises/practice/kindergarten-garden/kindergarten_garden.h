#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using child_index_t = std::uint8_t;

enum class Plant
{
    grass,
    clover,
    radishes,
    violets
}; /* MISRA C++: add semicolon after enum class */

// Alias for test compatibility
using Plants = Plant;

// Free function for test compatibility
std::vector<Plant> plants(const std::string& diagram, const std::string& child);

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<Plant> plants(const std::string& child) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> children_;
    static Plant plant_from_char(char c);
    static child_index_t child_index(const std::string& child);
}; /* MISRA C++: add semicolon after class */

} // namespace kindergarten_garden
