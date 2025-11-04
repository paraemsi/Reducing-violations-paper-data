#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

using student_index_t = std::uint8_t;

enum class Plants
{
    clover,
    grass,
    radishes,
    violets
};

class kindergarten_garden
{
public:
    explicit kindergarten_garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

    // Static function for test compatibility
    static std::vector<Plants> plants(const std::string& diagram, const std::string& student);

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> students;
    static student_index_t get_student_index(const std::string& student);
};

}  // namespace kindergarten_garden
