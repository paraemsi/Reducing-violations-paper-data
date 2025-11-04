#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <array>

namespace kindergarten_garden {

using index_t = std::uint8_t;

enum class Plants
{
    grass,
    clover,
    radishes,
    violets
};

class garden
{
public:


    explicit garden(const std::string& diagram);

    std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> s_students;
    static Plants plant_enum(char code);
    static index_t student_index(const std::string& student);
};

// Standalone function for test compatibility
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

} // namespace kindergarten_garden
