#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using student_index_t = std::uint8_t;

enum class Plants
{
    grass,
    clover,
    radishes,
    violets
}; // MISRA C++: add semicolon after enum class

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plants plant_from_char(char c);
    static student_index_t student_index(const std::string& student);
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

} // namespace kindergarten_garden
