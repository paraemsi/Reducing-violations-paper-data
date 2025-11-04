#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

    // Converts a number represented as a sequence of digits in input_base
    // to a sequence of digits in output_base.
    // Throws std::invalid_argument if input is invalid.
    [[nodiscard]] auto convert(std::int32_t input_base, std::vector<int> const& input_digits, std::int32_t output_base) -> std::vector<int>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
