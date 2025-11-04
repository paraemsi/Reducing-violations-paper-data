#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plant {
    grass,
    clover,
    radishes,
    violets
};

class kindergarten_garden {
public:
    explicit kindergarten_garden(const std::string& diagram);

    std::vector<Plant> plants(const std::string& student) const;

private:
    std::vector<std::string> rows_;
    std::vector<std::string> students_;
    std::map<char, Plant> plant_map_;

    void initialize_students();
    void initialize_plant_map();
    int student_index(const std::string& student) const;
};

// Free function for test compatibility
std::vector<Plant> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
