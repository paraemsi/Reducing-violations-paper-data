#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

/* Enumeration describing the allowed plant types. */
enum class Plants
{
    grass,
    clover,
    radishes,
    violets
};

/* Class representing the kindergarten garden diagram. */
class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = std::vector<std::string>{});

    std::array<Plants, 4U> plants(const std::string& student) const;

private:
    static const std::array<std::string, 12U> default_students;

    std::string m_row0;
    std::string m_row1;
    std::vector<std::string> m_students;
};

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student,
                              const std::vector<std::string>& students = std::vector<std::string>{});

}  // namespace kindergarten_garden
