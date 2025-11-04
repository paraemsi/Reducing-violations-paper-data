#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant { grass, clover, radishes, violets };

enum class Plants { grass, clover, radishes, violets };

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
    std::vector<std::string> students_;

    static const std::vector<std::string>& default_students();
    static plant from_char(char c);
    std::size_t index_for_student(const std::string& student) const;
};

}  // namespace kindergarten_garden
