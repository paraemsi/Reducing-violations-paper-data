#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};
using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> m_rows;
    std::vector<std::string> m_students;
};

}  // namespace kindergarten_garden
