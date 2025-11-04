#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

typedef std::uint8_t index_t;

enum class Plant
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

    std::vector<Plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plant char_to_plant(char c);
    static index_t student_index(const std::string& student);
}; // MISRA C++: add semicolon after class

// Add free function for test compatibility
std::vector<Plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
