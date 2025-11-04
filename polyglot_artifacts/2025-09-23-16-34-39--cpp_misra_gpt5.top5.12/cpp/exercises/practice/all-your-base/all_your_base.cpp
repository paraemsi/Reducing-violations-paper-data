#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

namespace {
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    using digits_t = std::vector<u32>;

    auto strip_leading_zeros(const digits_t& digits) -> digits_t
    {
        digits_t out{};
        out.reserve(digits.size());

        bool seen_non_zero = false;
        for (u32 d : digits) {
            if ((!seen_non_zero) && (d == static_cast<u32>(0U))) {
                // skip
            } else {
                out.push_back(d);
                seen_non_zero = true;
            }
        }
        return out;
    }
}  // unnamed namespace

auto convert(u32 in_base, const digits_t& digits, u32 out_base) -> digits_t
{
    if ((in_base < static_cast<u32>(2U)) || (out_base < static_cast<u32>(2U))) {
        throw std::invalid_argument("base must be >= 2");
    }

    digits_t src = strip_leading_zeros(digits);

    if (src.empty()) {
        return digits_t{};
    }

    for (u32 d : src) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    digits_t result{};

    while (!src.empty()) {
        std::uint64_t carry = static_cast<std::uint64_t>(0U);
        digits_t quotient{};
        quotient.reserve(src.size());

        bool started = false;
        for (u32 d : src) {
            std::uint64_t value =
                (carry * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(d);
            std::uint64_t q64 = value / static_cast<std::uint64_t>(out_base);
            std::uint64_t r64 = value % static_cast<std::uint64_t>(out_base);

            u32 q = static_cast<u32>(q64);  // safe: q64 < in_base <= UINT32_MAX
            u32 r = static_cast<u32>(r64);  // safe: r64 < out_base <= UINT32_MAX

            if ((!started) && (q == static_cast<u32>(0U))) {
                // skip leading zeros in the quotient
            } else {
                quotient.push_back(q);
                started = true;
            }

            carry = static_cast<std::uint64_t>(r);
        }

        result.push_back(static_cast<u32>(carry));
        src = std::move(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
