#pragma once

#include <cstddef>
#include <array>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
enum class Plants { clover, grass, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
    static plant map_char(char c);
    static std::size_t student_index(const std::string& student);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
