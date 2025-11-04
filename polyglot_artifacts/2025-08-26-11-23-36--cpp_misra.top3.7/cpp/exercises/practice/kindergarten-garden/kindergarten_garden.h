#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using index_t = std::uint8_t;

enum class Plant
{
    grass,
    clover,
    radishes,
    violets
}; // MISRA C++: semicolon after enum class

class Garden
{
public:
    explicit Garden(const std::string& diagram);

    std::vector<Plant> plants(const std::string& student) const;

private:
// Member variables and private methods
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plant char_to_plant(char c);
    static index_t student_index(const std::string& student);
}; // MISRA C++: semicolon after class

// Free function for test compatibility
std::vector<Plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
