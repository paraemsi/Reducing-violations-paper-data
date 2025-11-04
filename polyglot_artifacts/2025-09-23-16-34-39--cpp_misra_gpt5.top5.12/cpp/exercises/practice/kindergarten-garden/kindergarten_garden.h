#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant {
    clover,
    grass,
    radishes,
    violets
};

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& name) const;

private:
    std::array<std::string, 2U> rows_{};
    static std::size_t student_index(const std::string& name) noexcept;
    static plant decode(const char c) noexcept;
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& name) noexcept;

}  // namespace kindergarten_garden
