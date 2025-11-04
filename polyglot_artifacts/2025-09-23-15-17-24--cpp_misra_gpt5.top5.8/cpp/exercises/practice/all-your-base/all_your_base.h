#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace all_your_base {

// Convert a sequence of digits from input_base to output_base.
// - digits: most-significant digit first
// - Returns: digits in output_base, most-significant digit first
// - Throws std::invalid_argument on invalid bases (< 2) or invalid digits.
template <typename UInt>
auto convert(std::uint32_t input_base, const std::vector<UInt>& digits, std::uint32_t output_base) -> std::vector<UInt>
{
    static_assert(
        (std::is_integral<UInt>::value) && (std::is_unsigned<UInt>::value) && (!std::is_same<UInt, bool>::value),
        "UInt must be an unsigned integral type (excluding bool).");

    if ((input_base < static_cast<std::uint32_t>(2U)) || (output_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2.");
    }

    if (digits.empty()) {
        return std::vector<UInt>{};
    }

    // Validate digits and strip leading zeros
    for (const UInt d : digits) {
        if (static_cast<std::uint64_t>(d) >= static_cast<std::uint64_t>(input_base)) {
            throw std::invalid_argument("Digit out of range for input base.");
        }
    }

    std::vector<UInt> src;
    src.reserve(digits.size());

    bool non_zero_seen = false;
    for (const UInt d : digits) {
        if (!non_zero_seen) {
            if (d != static_cast<UInt>(0U)) {
                non_zero_seen = true;
            }
        }
        if (non_zero_seen) {
            src.push_back(d);
        }
    }

    if (!non_zero_seen) {
        return std::vector<UInt>{ static_cast<UInt>(0U) };
    }

    std::vector<UInt> result;
    const std::uint64_t in_base64 = static_cast<std::uint64_t>(input_base);
    const std::uint64_t out_base64 = static_cast<std::uint64_t>(output_base);

    // Repeated division algorithm to avoid large intermediate integers
    while (!src.empty()) {
        std::vector<UInt> quotient;
        quotient.reserve(src.size());

        std::uint64_t remainder = static_cast<std::uint64_t>(0U);
        bool started = false;

        for (const UInt d : src) {
            const std::uint64_t value = (remainder * in_base64) + static_cast<std::uint64_t>(d);
            const std::uint64_t q = (value / out_base64);
            remainder = (value % out_base64);

            if ((q != static_cast<std::uint64_t>(0U)) || (started)) {
                if (q > static_cast<std::uint64_t>(std::numeric_limits<UInt>::max())) {
                    throw std::overflow_error("Output digit does not fit in destination UInt type.");
                }
                quotient.push_back(static_cast<UInt>(q));
                started = true;
            }
        }

        if (remainder > static_cast<std::uint64_t>(std::numeric_limits<UInt>::max())) {
            throw std::overflow_error("Output digit does not fit in destination UInt type.");
        }
        result.push_back(static_cast<UInt>(remainder));
        src = std::move(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
