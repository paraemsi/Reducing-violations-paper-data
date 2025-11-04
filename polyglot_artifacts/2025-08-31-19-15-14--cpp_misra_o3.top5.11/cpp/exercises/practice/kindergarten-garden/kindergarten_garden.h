#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

// Enumeration of the allowed plants in the garden.
enum class Plants
{
    grass,
    clover,
    radishes,
    violets
};

// Class representing a kindergarten garden.
class garden
{
public:
    // Construct a garden from a diagram using the default, alphabetically
    // ordered list of student names.
    explicit garden(const std::string& diagram);

    // Construct a garden from a diagram and an explicit list of student names.
    garden(const std::string& diagram,
           const std::vector<std::string>& students);

    // Retrieve the four plants assigned to a particular student.
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> m_assignments;

    static std::vector<std::string> default_students();
    static Plants char_to_plant(char symbol);
};

// Convenience free function returning the four plants for a student based
// solely on a diagram and the student's name.
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student);

}  // namespace kindergarten_garden
