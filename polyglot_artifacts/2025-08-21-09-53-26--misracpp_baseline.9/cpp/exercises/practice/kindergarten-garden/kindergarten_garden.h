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
    Garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    std::vector<std::string> students_;
    std::map<char, Plants> plant_map_;

    void initialize_students();
    void initialize_plant_map();
    int student_index(const std::string& student) const;
};

// Free function for tests
std::vector<Plants> plants(const std::string& diagram, const std::string& student);

} // namespace kindergarten_garden
