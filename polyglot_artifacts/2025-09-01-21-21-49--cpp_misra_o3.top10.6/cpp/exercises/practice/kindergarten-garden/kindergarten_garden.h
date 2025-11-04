#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

/* Enumeration of every supported plant type */
enum class Plants
{
    clover,
    grass,
    radishes,
    violets
};

/* Default, alphabetically-sorted class roster */
extern const std::vector<std::string> default_student_names;

/* Represents one kindergarten garden and the cup-to-student assignments */
class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_student_names);

    /* Return the four plants assigned to the requested student */
    std::array<Plants, 4> plants(const std::string& student) const;

private:
    static Plants char_to_plant(char input);

    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;
};

/* Convenience free-function used by the tests */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
