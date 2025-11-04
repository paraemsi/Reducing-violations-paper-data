#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

// Enumeration of the four possible plants a cup may contain.
enum class Plants { radishes, clover, grass, violets };

// A garden knows the diagram and which plants belong to which student.
class garden {
public:
    // Construct a garden using the default, alphabetically-sorted student list.
    explicit garden(const std::string& diagram);

    // Construct a garden with a custom set of students (sorted internally).
    garden(const std::string& diagram, const std::vector<std::string>& students);

    // Retrieve the four plants assigned to the requested student.
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::vector<std::string> students_;                                   // Sorted list of students
    std::unordered_map<std::string, std::vector<Plants>> assignments_;    // Cached assignments

    static std::vector<std::string> default_students();                   // Default student names
    static Plants char_to_plant(char c);                                  // Map diagram char → plant
    void assign(const std::string& diagram);                              // Fill assignments_
};

// Convenient free-functions required by tests ----------------------------- //
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students);

}  // namespace kindergarten_garden
