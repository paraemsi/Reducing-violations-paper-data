#pragma once

#include <string>
#include <vector>
#include <array>
#include <map>

namespace kindergarten_garden {

// Enumeration of possible plants.
enum class Plants { grass, clover, radishes, violets };

// Represents the entire kindergarten garden.
class garden {
public:
    // Construct a garden from a two-row diagram.  If no student list is
    // provided, the default alphabetical roster is used.
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    // Return the four plants assigned to the given student.
    std::vector<Plants> plants(const std::string& student) const;

private:
    // Default student roster, kept out of the header to avoid multiple
    // definitions issues.
    static const std::vector<std::string> default_students_;

    // Mapping from student name to their four plants.
    std::map<std::string, std::vector<Plants>> assignments_;
};

std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
