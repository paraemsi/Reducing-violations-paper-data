#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace all_your_base {

namespace {
constexpr std::uint32_t kMinBase = static_cast<std::uint32_t>(2U);

inline void validate_bases(std::uint32_t in_base, std::uint32_t out_base)
{
    if ((in_base < kMinBase) || (out_base < kMinBase)) {
        throw std::invalid_argument("Bases must be >= 2");
    }
}

inline void validate_digits(all_your_base::digits_t const& digits, std::uint32_t in_base)
{
    for (all_your_base::digit_t d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("Digit outside input base");
        }
    }
}

inline bool is_all_zero(all_your_base::digits_t const& digits)
{
    for (all_your_base::digit_t d : digits) {
        if (d != static_cast<digit_t>(0U)) {
            return false;
        }
    }
    return true;
}

inline all_your_base::digits_t strip_leading_zeros(all_your_base::digits_t const& digits)
{
    all_your_base::digits_t out{};
    bool started = false;
    for (all_your_base::digit_t d : digits) {
        if ((!started) && (d == static_cast<digit_t>(0U))) {
            // skip
        } else {
            started = true;
            out.push_back(d);
        }
    }
    return out;
}
}  // namespace

auto convert(std::uint32_t in_base, digits_t const& in_digits, std::uint32_t out_base) -> digits_t
{
    validate_bases(in_base, out_base);
    validate_digits(in_digits, in_base);

    if ((in_digits.empty()) || (is_all_zero(in_digits))) {
        return digits_t{static_cast<digit_t>(0U)};
    }

    digits_t current = strip_leading_zeros(in_digits);
    digits_t result_reversed{};
    result_reversed.reserve(current.size());

    while (!current.empty()) {
        digits_t next{};
        next.reserve(current.size());

        std::uint64_t remainder = static_cast<std::uint64_t>(0U);
        for (digit_t d : current) {
            // acc = remainder * in_base + d (do in 64-bit to avoid overflow)
            std::uint64_t acc = (remainder * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(d);
            std::uint64_t q64 = acc / static_cast<std::uint64_t>(out_base);
            std::uint64_t r64 = acc % static_cast<std::uint64_t>(out_base);

            if ((!next.empty()) || (q64 != static_cast<std::uint64_t>(0U))) {
                next.push_back(static_cast<digit_t>(q64));
            }
            remainder = r64;
        }

        result_reversed.push_back(static_cast<digit_t>(remainder));
        current = std::move(next);
    }

    std::reverse(result_reversed.begin(), result_reversed.end());
    return result_reversed;
}

}  // namespace all_your_base
