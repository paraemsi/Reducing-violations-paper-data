#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { grass, clover, radishes, violets };

class garden {
public:
    // Construct a garden from the diagram and, optionally, a custom list of students.
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    // Return the four plants assigned to the requested student.
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> assignment_;

    // Default roster in alphabetical order.
    static const std::vector<std::string> default_students_;
    static Plants to_plant(char c);
};

// Free-function interface expected by the tests.
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students = {});

}  // namespace kindergarten_garden
