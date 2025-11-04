#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using index_t = std::uint8_t;

// For test compatibility, provide alias Plants = plant
enum class plant
{
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

class garden
{
public:
    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> m_students;
    static plant decode_plant(char code);
    static index_t student_index(const std::string& student);
};

// Free function for test compatibility
std::vector<plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
