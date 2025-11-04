#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <iosfwd>

namespace kindergarten_garden {

// Enumeration of the possible plants.
enum class Plants { grass, clover, radishes, violets };

// A garden stores the mapping of students to their four plants.
class garden {
public:
    // Construct a garden using the default alphabetical student list.
    explicit garden(const std::string& diagram);

    // Construct a garden with a custom list of students.
    garden(const std::string& diagram, const std::vector<std::string>& students);

    // Return the four plants that belong to the given student.
    std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;

    static Plants char_to_plant(char c);
    static const std::vector<std::string> default_students_;
};

/* Free-function wrapper and helpers expected by the unit tests */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

std::ostream& operator<<(std::ostream& os, Plants p);

}  // namespace kindergarten_garden
