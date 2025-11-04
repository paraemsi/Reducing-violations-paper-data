#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants : std::uint8_t
{
    clover,
    grass,
    radishes,
    violets
};

class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> m_students;
    std::vector<std::vector<Plants>> m_assignments;

    static Plants char_to_plant(char code);
    static std::vector<std::string> default_students();
};

std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student);

}  // namespace kindergarten_garden
