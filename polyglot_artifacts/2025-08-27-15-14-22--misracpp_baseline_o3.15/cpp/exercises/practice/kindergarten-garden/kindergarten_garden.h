#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <string_view>

namespace kindergarten_garden {

// Enumeration representing each type of plant in the garden.
enum class Plants { clover, grass, radishes, violets };

// Default classroom roster in alphabetical order.
extern const std::vector<std::string> default_students;

class garden {
public:
    // Construct a garden from a diagram and (optionally) a custom, unordered
    // list of student names.  The list will be sorted alphabetically to
    // determine planting order.
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_students);

    // Return the four plants assigned to the requested student.
    std::array<Plants, 4> plants(std::string_view student_name) const;

private:
    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;
};

std::array<Plants, 4> plants(std::string_view diagram,
                             std::string_view student_name);

}  // namespace kindergarten_garden
