#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plants {
    violets,
    radishes,
    clover,
    grass
};

class garden {
public:
    garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> student_plants_;
    static const std::vector<std::string> students_;
    static Plants char_to_plant(char c);
};

}  // namespace kindergarten_garden
