#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant
{
    clover,
    grass,
    radishes,
    violets
};

enum class Plants
{
    radishes,
    clover,
    grass,
    violets
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static std::size_t student_index(const std::string& student);
    static plant char_to_plant(char c);
};

}  // namespace kindergarten_garden
