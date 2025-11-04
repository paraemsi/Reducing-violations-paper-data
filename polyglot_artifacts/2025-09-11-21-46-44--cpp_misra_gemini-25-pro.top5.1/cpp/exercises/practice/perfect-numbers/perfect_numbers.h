#pragma once

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t {
    perfect,
    abundant,
    deficient
};

classification classify(std::int32_t number);

}  // namespace perfect_numbers
