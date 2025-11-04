#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <cstddef>
#include <cstdint>

namespace kindergarten_garden {

/* Enumeration representing the four possible plants. */
enum class Plants : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:


    /* Construct a garden from the diagram and an optional, pre-defined
       student list.  If no list is supplied, the default alphabetical
       roster is used. */
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = default_student_list());

    /* Return the four plants assigned to the specified student. */
    std::vector<Plants> plants(const std::string& student) const;


private:
    /* Helper returning the canonical list of students in alphabetical order. */
    static const std::vector<std::string>& default_student_list();

    /* Translate the diagram encoding to the enumeration. */
    static Plants char_to_plant(char code);

    /* Map each student to their four plants. */
    std::unordered_map<std::string, std::vector<Plants>> m_assignments;
};

/* ---------- free helper function ---------------------------------------- */
inline std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    garden g(diagram);  // uses default alphabetical roster
    auto const vec {g.plants(student)};

    std::array<Plants, 4U> result {};
    for (std::size_t i {0U}; i < 4U; ++i) {
        result[i] = vec[i];
    }
    return result;
}

}  // namespace kindergarten_garden
