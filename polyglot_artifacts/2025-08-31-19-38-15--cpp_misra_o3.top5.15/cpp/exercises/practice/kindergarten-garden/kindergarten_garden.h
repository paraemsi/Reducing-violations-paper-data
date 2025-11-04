#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

/* Enumeration representing the four kinds of plants. */
enum class plant
{
    clover,
    grass,
    radishes,
    violets
};

/* Alias required by the test-suite.  The underlying enumeration is
 * identical, only the spelling of the type-name differs.            */
using Plants = plant;

/* Class representing a kindergarten garden. */
class garden
{
public:
    /* Helper that provides the default roster in alphabetical order. */
    static std::vector<std::string> default_students();

    /* Construct from the diagram string (two rows, separated by '\n').
       If no explicit student list is supplied, the default alphabetical
       roster is used. */
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_students());

    /* Return the four plants assigned to the given student name.
       If the name is unknown, an empty vector is returned. */
    std::vector<plant> plants(const std::string& student) const;

private:
    using index_t = std::size_t;
    std::unordered_map<std::string, std::vector<plant>> m_assignments;
};

/* Convenience free-function expected by the tests.  It builds an
 * internal `garden` from the given diagram (and optional roster) and
 * returns the four plants belonging to the requested student.       */
std::array<Plants, 4U> plants(
    const std::string& diagram,
    const std::string& student,
    const std::vector<std::string>& students = garden::default_students());

}  // namespace kindergarten_garden
