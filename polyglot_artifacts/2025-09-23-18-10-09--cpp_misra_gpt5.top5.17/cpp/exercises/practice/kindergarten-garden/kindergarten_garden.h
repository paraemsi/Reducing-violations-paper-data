#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::array<std::string, 2U> rows_{};

    static std::size_t student_index(const std::string& name);
    static Plants char_to_plant(std::string::value_type c);
};

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
