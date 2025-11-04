#include "all_your_base.h"

#include <algorithm>   // std::reverse
#include <stdexcept>   // std::invalid_argument

namespace all_your_base {

[[nodiscard]] auto convert(std::uint32_t from_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    if (from_base < static_cast<std::uint32_t>(2U)) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < static_cast<std::uint32_t>(2U)) {
        throw std::invalid_argument("output base must be >= 2");
    }
    if (digits.empty()) {
        throw std::invalid_argument("digits vector is empty");
    }

    /* Validate digits and compute the numeric value in a wider type */
    std::uint64_t value{0U};
    for (const std::uint32_t digit : digits) {
        if (digit >= from_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        value = (value * static_cast<std::uint64_t>(from_base))
              + static_cast<std::uint64_t>(digit);
    }

    /* Special-case zero */
    if (value == static_cast<std::uint64_t>(0U)) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    std::vector<std::uint32_t> result{};
    while (value > static_cast<std::uint64_t>(0U)) {
        const std::uint32_t remainder{
            static_cast<std::uint32_t>(
                value % static_cast<std::uint64_t>(to_base)
            )
        };
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

} // namespace all_your_base
