#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { grass, clover, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::map<std::string, std::array<Plants, 4>> assignments_;

    static Plants char_to_plant(char c);
    static std::vector<std::string> default_students();
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
