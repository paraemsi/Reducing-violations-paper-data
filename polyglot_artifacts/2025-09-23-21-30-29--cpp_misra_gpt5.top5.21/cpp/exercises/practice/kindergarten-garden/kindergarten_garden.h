#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<Plants> plants(const std::string& student) const;

private:
    static std::size_t student_index(const std::string& student);
    static Plants char_to_plant(char c);

    std::array<std::string, 2U> rows_{};
};

}  // namespace kindergarten_garden
