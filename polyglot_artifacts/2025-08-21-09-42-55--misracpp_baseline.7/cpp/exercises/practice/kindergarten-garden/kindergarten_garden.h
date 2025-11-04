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

class Garden {
public:
    Garden(const std::string& diagram,
           const std::vector<std::string>& students = std::vector<std::string>());

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants> > student_plants_;
    static Plants char_to_plant(char c);
    static const std::vector<std::string> default_students_;
};

// Free function for test compatibility
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
