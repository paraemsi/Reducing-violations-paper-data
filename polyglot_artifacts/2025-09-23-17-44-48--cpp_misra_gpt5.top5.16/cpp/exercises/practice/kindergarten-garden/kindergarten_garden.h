#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

using Plants = plant;

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string m_row1;
    std::string m_row2;
    std::vector<std::string> m_students;

    static std::vector<std::string> default_students();
};

}  // namespace kindergarten_garden
