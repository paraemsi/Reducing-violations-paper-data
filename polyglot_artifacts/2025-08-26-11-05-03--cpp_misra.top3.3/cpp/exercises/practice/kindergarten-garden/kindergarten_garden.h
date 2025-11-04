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
};

using Plants = Plant;

class Garden
{
public:
    explicit Garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    static const std::vector<std::string> students_;
    static Plant char_to_plant(char c);
    static index_t student_index(const std::string& student);
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
