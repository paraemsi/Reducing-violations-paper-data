#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

typedef std::uint8_t student_index_t;

enum class Plants
{
    grass,
    clover,
    radishes,
    violets
}; // MISRA C++: enum class should be terminated with a semicolon

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

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
