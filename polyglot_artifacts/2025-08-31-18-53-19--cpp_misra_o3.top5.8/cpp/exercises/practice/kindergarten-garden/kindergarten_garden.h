#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

/*  Enumeration of the four possible plants. */
enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

/*  The garden class parses the diagram once at construction and
    answers queries for the plants assigned to each student. */
class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::array<Plants, 4U> plants(const std::string& student) const;

private:
    std::array<std::string, 2U> rows_{};
    std::vector<std::string> students_{};

    static Plants char_to_plant(char code);
};

/*  Convenience free function required by the tests. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student);

}  // namespace kindergarten_garden
