#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plants {
    radishes,
    clover,
    grass,
    violets
};

class Garden {
public:
    Garden(const std::string& diagram,
           const std::vector<std::string>& students);

    std::vector<Plants> plants(const std::string& student) const;

private:


    std::map<std::string, std::vector<Plants>> student_plants_;
    static Plants char_to_plant(char c);
};

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
