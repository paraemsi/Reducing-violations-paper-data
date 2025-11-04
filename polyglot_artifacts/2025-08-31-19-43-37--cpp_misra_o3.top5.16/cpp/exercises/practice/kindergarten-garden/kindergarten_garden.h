#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    violets,
    radishes,
    clover,
    grass
};

using plant = Plants;

/* Return the four plants assigned to the given student name
 * using the default alphabetical student list.
 */
[[nodiscard]] std::array<Plants, 4U> plants(std::string_view diagram,
                                            std::string_view student);

class garden {
public:
    static std::vector<std::string> default_students();

    explicit garden(std::string_view diagram,
                    std::vector<std::string> const& students = default_students());

    std::vector<plant> plants(std::string_view student) const;

private:
    std::vector<std::string> m_students;
    std::array<std::string, 2U> m_rows{};

    static plant to_plant(char cup);
};

}  // namespace kindergarten_garden
