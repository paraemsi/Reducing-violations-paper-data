#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plant {
    violets,
    radishes,
    clover,
    grass
};

using Plants = Plant;

class kindergarten_garden {
public:
    explicit kindergarten_garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> students_;
    std::map<std::string, std::vector<Plants>> student_plants_;

    static std::vector<std::string> default_students_;
    static Plants char_to_plant(char c);
    void parse_diagram(const std::string& diagram);
};

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden

std::vector<Plants> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
