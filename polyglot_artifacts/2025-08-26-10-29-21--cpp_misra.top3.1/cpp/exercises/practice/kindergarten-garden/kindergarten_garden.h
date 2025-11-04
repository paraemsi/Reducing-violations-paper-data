#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using index_t = std::uint8_t;

enum class plant
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

    std::vector<plant> plants(const std::string& student) const;

    // Add a free function for test compatibility
    static std::vector<plant> plants(const std::string& diagram, const std::string& student);

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> m_students;

    static plant decode_plant(char code);
    static index_t student_index(const std::string& student);
};

}  // namespace kindergarten_garden
