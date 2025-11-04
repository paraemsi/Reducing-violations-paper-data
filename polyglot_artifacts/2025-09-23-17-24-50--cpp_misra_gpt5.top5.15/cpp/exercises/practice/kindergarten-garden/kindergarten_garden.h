#pragma once

#include <cstddef>
#include <cstdint>
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

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::string m_row1;
    std::string m_row2;

    static const std::vector<std::string>& students_order();
    static plant to_plant(std::string::value_type code);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
