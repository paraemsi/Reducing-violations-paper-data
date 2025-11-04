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

class kindergarten_garden {
public:
    kindergarten_garden(const std::string& diagram,
                        const std::vector<std::string>& students);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> student_plants_;
    static Plants char_to_plant(char c);
};

// Static interface for test cases that expect a free function
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
