#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using index_t = std::uint8_t;

enum class Plants
{
    clover,
    grass,
    radishes,
    violets
};

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plants char_to_plant(char c);
    static index_t student_index(const std::string& student);
};

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
