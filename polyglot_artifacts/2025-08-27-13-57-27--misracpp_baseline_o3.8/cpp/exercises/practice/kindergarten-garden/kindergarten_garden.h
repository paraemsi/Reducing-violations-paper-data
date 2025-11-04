#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

 // Enumeration listing every possible plant
enum class Plants { grass, clover, radishes, violets };

// Default class roster in alphabetical order
extern const std::vector<std::string> default_students;

class garden {
public:
    // Construct from diagram plus optional custom student list
    explicit garden(const std::string& diagram,
                    std::vector<std::string> students = default_students);

    // Return the four plants assigned to the given student
    std::array<Plants, 4> plants(const std::string& student) const;

private:
    // Translate diagram character to plant enumeration
    static Plants char_to_plant(char c);
    std::map<std::string, std::array<Plants, 4>> assignments_;
};

// Convenience free function used by the tests
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
