#pragma once

#include <string>
#include <vector>
#include <map>
#include <array>

namespace kindergarten_garden {

enum class Plants { grass, clover, radishes, violets };

class garden {
public:
    // Construct a garden from a diagram. If no custom list of students is
    // supplied, the default class roster is used.
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = std::vector<std::string>());

    // Return the four plants assigned to the requested student.
    std::array<Plants, 4> plants(const std::string& student) const;

private:
    static const std::vector<std::string> default_students;
    std::map<std::string, std::array<Plants, 4>> assignments;

    static Plants char_to_plant(char c);
};

/*
 * Convenience free function required by the tests.
 * Builds a temporary garden from the diagram and returns the requested
 * student's four assigned plants.
 */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students = std::vector<std::string>());

}  // namespace kindergarten_garden
