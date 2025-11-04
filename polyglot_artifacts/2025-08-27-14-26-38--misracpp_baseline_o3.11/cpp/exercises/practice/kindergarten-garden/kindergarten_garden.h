#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <array>

namespace kindergarten_garden {

// Enumeration of the four possible plants.
enum class plant {
    grass,
    clover,
    radishes,
    violets
};

// Public alias expected by the tests — allows accessing enumerators as
// kindergarten_garden::Plants::grass etc.
using Plants = plant;

// A garden object parses the diagram once in the constructor
// and then allows constant-time lookup of any student's plants.
class garden {
public:

    // If no explicit student list is supplied, the default alphabetical
    // roster is used (see default_students declaration above).
    explicit garden(std::string_view diagram,
                    const std::vector<std::string>& students = default_students);


    // Return the four plants belonging to the named student.
    const std::vector<plant>& plants(std::string_view student) const;

private:
    std::map<std::string, std::vector<plant>> assignments_;

    // Helper to convert a single diagram character to the
    // corresponding plant enumeration value.
    static plant char_to_plant(char c);

    // The default 12-student roster, already in alphabetical order.
    static const std::vector<std::string> default_students;
};

// Convenience free-function required by the tests.
// Builds a temporary garden from the diagram and returns the
// 4 plants assigned to the requested student.
std::array<Plants, 4> plants(std::string_view diagram,
                             std::string_view student);

}  // namespace kindergarten_garden
