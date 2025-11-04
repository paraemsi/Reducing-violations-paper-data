#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

enum class Plant : std::uint8_t {
    radishes,
    clover,
    grass,
    violets
};

class Garden {
public:
    explicit Garden(const std::string& diagram);

    std::vector<Plant> plants(const std::string& student) const;

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> students;
    static Plant char_to_plant(char c);
};

std::vector<Plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
