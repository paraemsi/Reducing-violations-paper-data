#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { clover, grass, radishes, violets };
using plant = Plants;

// Returns the default, alphabetically sorted list of student names.
std::vector<std::string> default_students();

// Convenience free function to retrieve a student's four plants from a diagram.
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram,
                    std::vector<std::string> students = default_students());

    std::vector<plant> plants(const std::string& student) const;

private:
    static plant char_to_plant(char c);

    std::map<std::string, std::vector<plant>> assignments_;
};

}  // namespace kindergarten_garden
