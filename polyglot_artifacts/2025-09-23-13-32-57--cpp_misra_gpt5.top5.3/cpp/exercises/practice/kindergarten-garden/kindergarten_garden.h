#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants : std::uint8_t { clover, grass, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram);
    std::array<Plants, 4U> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static Plants to_plant(char code) noexcept;
    static std::size_t student_index(const std::string& student) noexcept;
};

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
