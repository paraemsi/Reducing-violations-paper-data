#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

static constexpr std::size_t cups_per_student = static_cast<std::size_t>(4U);

std::array<Plants, cups_per_student> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<Plants> plants(const std::string& student) const;

private:
    std::array<std::string, static_cast<std::size_t>(2U)> rows_{};
};

}  // namespace kindergarten_garden
