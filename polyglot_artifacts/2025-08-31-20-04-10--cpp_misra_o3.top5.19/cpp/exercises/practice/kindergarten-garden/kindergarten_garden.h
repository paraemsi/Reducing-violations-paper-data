#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace kindergarten_garden {

/* Enumeration of the four possible plants in the garden */
enum class Plants
{
    clover,
    grass,
    radishes,
    violets
};

/* Class that represents the kindergarten garden diagram and allows
 * querying the four plants assigned to an individual student. */
class garden
{
public:
    /* Return the default alphabetical roster of students. */
    static std::vector<std::string> default_students();

    /* Construct a garden from its textual diagram.  If the caller does not
     * supply an explicit list of student names, the default alphabetical
     * roster defined by the exercise specification is used. */
    garden(const std::string& diagram,
           const std::vector<std::string>& students = default_students());

    /* Return the four plants (two per row) assigned to the given student. */
    [[nodiscard]] std::array<Plants, 4U> plants(const std::string& student) const;

private:
    /* Mapping from student name to the four-plant array allocated to them. */
    std::map<std::string, std::array<Plants, 4U>> assignments_;

    /* Helpers */
    static Plants char_to_plant(char c);
};

/* Convenience free function to satisfy the test suite. */
std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
