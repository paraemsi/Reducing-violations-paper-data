#pragma once

#include <string_view>
#include <array>
#include <cstddef>
#include <cstdint>

namespace kindergarten_garden {

enum class Plants : std::uint8_t {
    clover,
    grass,
    radishes,
    violets
};

[[nodiscard]] std::array<Plants, 4U> plants(std::string_view diagram,
                                            std::string_view student);

}  // namespace kindergarten_garden
