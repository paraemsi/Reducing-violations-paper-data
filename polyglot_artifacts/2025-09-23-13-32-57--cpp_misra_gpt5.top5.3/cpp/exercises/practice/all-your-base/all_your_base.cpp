#include "all_your_base.h"

#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cstdint>

namespace all_your_base {

static auto trim_leading_zeros(const std::vector<digit_type>& digits) -> std::vector<digit_type>
{
    std::vector<digit_type> result{};
    bool non_zero_seen{false};
    for (const digit_type d : digits) {
        if (!non_zero_seen) {
            if (d != static_cast<digit_type>(0)) {
                non_zero_seen = true;
            } else {
                // still trimming leading zeros
            }
        }
        if (non_zero_seen) {
            result.push_back(d);
        } else {
            // skip leading zero
        }
    }
    return result;
}

auto convert(base_type in_base, const std::vector<digit_type>& digits, base_type out_base) -> std::vector<digit_type>
{
    if ((in_base < static_cast<base_type>(2)) || (out_base < static_cast<base_type>(2))) {
        throw std::invalid_argument("base must be >= 2");
    } else {
        // bases are valid
    }

    // Trim leading zeros from input
    std::vector<digit_type> source = trim_leading_zeros(digits);

    if (source.empty()) {
        return std::vector<digit_type>{static_cast<digit_type>(0)};
    } else {
        // continue
    }

    // Validate digits range once
    for (const digit_type d : source) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        } else {
            // ok
        }
    }

    // Repeated division algorithm to avoid large intermediate integers
    std::vector<digit_type> remainders{};

    while (!source.empty()) {
        std::vector<digit_type> quotient{};
        quotient.reserve(source.size());

        std::uint64_t remainder64{static_cast<std::uint64_t>(0)};
        bool started{false};

        for (const digit_type d : source) {
            const std::uint64_t tmp = (remainder64 * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(d);
            const std::uint64_t q64 = (tmp / static_cast<std::uint64_t>(out_base));
            remainder64 = (tmp % static_cast<std::uint64_t>(out_base));

            if ((q64 != static_cast<std::uint64_t>(0)) || started) {
                if (q64 > static_cast<std::uint64_t>(std::numeric_limits<digit_type>::max())) {
                    throw std::overflow_error("quotient digit does not fit in digit_type");
                } else {
                    // ok
                }
                quotient.push_back(static_cast<digit_type>(q64));
                started = true;
            } else {
                // still suppressing leading zeros in quotient
            }
        }

        if (remainder64 > static_cast<std::uint64_t>(std::numeric_limits<digit_type>::max())) {
            throw std::overflow_error("remainder does not fit in digit_type");
        } else {
            // ok
        }
        remainders.push_back(static_cast<digit_type>(remainder64));
        source = quotient;
    }

    // Reverse remainders to produce most-significant first
    std::reverse(remainders.begin(), remainders.end());
    return remainders;
}

}  // namespace all_your_base
