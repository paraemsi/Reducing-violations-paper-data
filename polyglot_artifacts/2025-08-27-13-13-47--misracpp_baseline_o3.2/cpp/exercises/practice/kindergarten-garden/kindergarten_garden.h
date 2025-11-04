#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <array>

namespace kindergarten_garden {

/* Enumeration of the four possible plants a cup can contain. */
enum class Plants { radishes, clover, grass, violets };

/* Alphabetical list of students used when no explicit list is supplied. */
extern const std::vector<std::string> default_students;

/* Represents the classroom garden and offers plant look-ups for each child. */
class garden {
public:
    /* The diagram is two rows separated by a single '\n'.
       Students will be sorted alphabetically as required by the rules. */
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_students);

    /* Return the four plants (2 cups in each row) belonging to the named child. */
    std::vector<Plants> plants(const std::string& student) const;

private:
    /* Helper translating diagram characters to the enum. */
    static Plants char_to_plant(char c);

    std::vector<std::string> m_students;  // sorted list of student names
    std::string m_row1;
    std::string m_row2;
};

/* Convenience free-function required by the tests. */
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
