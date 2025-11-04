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
    explicit kindergarten_garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

    // Static function for the test suite
    static std::vector<Plants> plants(const std::string& diagram, const std::string& student);

private:
    std::map<std::string, std::vector<Plants>> student_plants_;
    static const std::vector<std::string> students_;
    static Plants char_to_plant(char c);
};

}  // namespace kindergarten_garden
