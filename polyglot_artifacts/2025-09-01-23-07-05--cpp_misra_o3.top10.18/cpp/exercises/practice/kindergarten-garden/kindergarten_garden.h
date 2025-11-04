#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

/* Represents a single plant type present in a cup. */
enum class Plants {
    violets,
    radishes,
    clover,
    grass
};

/* A parsed garden that can answer which plants belong to which student. */
class garden final {
public:
    explicit garden(const std::string& diagram);
    explicit garden(
        const std::string& diagram,
        const std::vector<std::string>& students);

    /* Return the four plants owned by the requested student.
       If the student name is not present, an empty vector is returned. */
    [[nodiscard]] std::array<Plants, 4U> plants(const std::string& student) const;

private:
    std::vector<std::string> m_students {};
    std::vector<std::string> m_rows     {};

    static Plants char_to_plant(char code);

    static const std::vector<std::string> default_students;
};

/* Convenience free-function expected by the tests. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student);

}  // namespace kindergarten_garden
