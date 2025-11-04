#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    std::vector<std::string> students_;
    std::unordered_map<std::string, std::size_t> index_by_student_;
};

}  // namespace kindergarten_garden
