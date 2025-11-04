#pragma once

#include <string>
#include <vector>
#include <map>
#include <array>

namespace kindergarten_garden {

enum class Plants { clover, grass, radishes, violets };
using plant = Plants;

// Convenience free function API used by tests.
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::map<std::string, std::array<Plants, 4>> assignments_;
};

}  // namespace kindergarten_garden
