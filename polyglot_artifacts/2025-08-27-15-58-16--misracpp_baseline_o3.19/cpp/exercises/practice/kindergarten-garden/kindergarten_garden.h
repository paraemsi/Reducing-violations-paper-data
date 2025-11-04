#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <unordered_map>

namespace kindergarten_garden {

// Enumeration of all possible plants.
enum class Plants { radishes, clover, grass, violets };

class Garden {
public:
    // Construct a garden using the default (alphabetically-ordered) student list.
    explicit Garden(std::string_view diagram);

    // Construct a garden with a custom list of students.
    // The list is alphabetically sorted before plants are assigned.
    Garden(std::string_view diagram, const std::vector<std::string>& students);

    // Return the four plants assigned to the given student.
    std::array<Plants,4> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::array<Plants,4>> assignments_;

    static Plants char_to_plant(char c);
    static const std::vector<std::string> default_students_;
};

std::array<Plants,4> plants(std::string_view diagram, const std::string& student);

}  // namespace kindergarten_garden
