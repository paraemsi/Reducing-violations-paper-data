#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <vector>

namespace kindergarten_garden {

enum class plant {
    grass,
    clover,
    radishes,
    violets
};

using Plants = plant;

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static std::string::size_type student_index(const std::string& student);
    static plant char_to_plant(const char ch);
};

}  // namespace kindergarten_garden
