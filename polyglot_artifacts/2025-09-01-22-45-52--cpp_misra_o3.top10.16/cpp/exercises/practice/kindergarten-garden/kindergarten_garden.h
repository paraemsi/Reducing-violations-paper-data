#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <string>
#include <vector>

namespace kindergarten_garden {

/*
 * Enum representing the four possible plants a student can have.
 */
enum class Plant {
    grass,
    clover,
    radishes,
    violets
};

/* Alias required by the test-suite. */
using Plants = Plant;

/*
 * Garden parses the supplied diagram once in the constructor
 * and stores every student's four plants in a fixed-size array.
 *
 * The students are ordered alphabetically:
 * Alice, Bob, Charlie, David, Eve, Fred, Ginny, Harriet,
 * Ileana, Joseph, Kincaid, Larry
 */
class Garden {
public:
    explicit Garden(std::string_view diagram);

    /*
     * Return the four plants belonging to the requested student.
     * Throws std::out_of_range if the name is unknown.
     */
    [[nodiscard]] std::array<Plant, 4U> plants(std::string_view student) const;

private:
    std::array<std::array<Plant, 4U>, 12U> m_student_plants{};

    [[nodiscard]] static std::uint32_t student_index(std::string_view name);
    [[nodiscard]] static Plant to_plant(char cup);
};

/* Free helper function expected by the tests. */
[[nodiscard]] std::array<Plant, 4U> plants(std::string_view diagram, std::string_view student);

}  // namespace kindergarten_garden
