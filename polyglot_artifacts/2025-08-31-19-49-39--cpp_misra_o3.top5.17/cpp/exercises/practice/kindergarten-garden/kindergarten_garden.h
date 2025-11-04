#pragma once

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>

namespace kindergarten_garden {

enum class Plants {
    radishes,
    clover,
    grass,
    violets
};

class garden {
public:
    static const std::vector<std::string>& default_students();

    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_students());

    std::vector<Plants> plants(const std::string& student) const;

private:
    using plant_list = std::vector<Plants>;
    std::unordered_map<std::string, plant_list> m_assignments;
};
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);
 
}  // namespace kindergarten_garden
