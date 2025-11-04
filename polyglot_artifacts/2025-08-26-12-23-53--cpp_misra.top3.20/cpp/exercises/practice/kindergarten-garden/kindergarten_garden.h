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
};

using index_t = std::uint8_t;

using Plants = plant;

class garden
{
public:

    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static plant decode_plant(char code);
    static index_t student_index(const std::string& student);
};

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
