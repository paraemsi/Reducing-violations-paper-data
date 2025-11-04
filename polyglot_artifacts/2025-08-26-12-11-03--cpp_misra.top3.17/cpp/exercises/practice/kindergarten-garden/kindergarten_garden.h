#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

enum class plant
{
    clover,
    grass,
    radishes,
    violets
}; // MISRA C++: semicolon after enum class

using index_t = std::uint8_t;

// Alias for test compatibility
using Plants = plant;

// Free function for test compatibility
std::vector<plant> plants(const std::string& diagram, const std::string& student);

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static plant decode_plant(char c);
    static index_t student_index(const std::string& student);
}; // MISRA C++: semicolon after class

}  // namespace kindergarten_garden
