#include "all_your_base.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>

namespace all_your_base {

namespace
{
    auto trim_leading_zeros(const std::vector<std::uint32_t>& digits)
        -> std::vector<std::uint32_t>
    {
        std::vector<std::uint32_t> trimmed{};
        std::size_t i{0U};
        while ((i < digits.size()) && (digits[i] == static_cast<std::uint32_t>(0U))) {
            ++i;
        }
        if (i == digits.size()) {
            trimmed.push_back(static_cast<std::uint32_t>(0U));
            return trimmed;
        }
        trimmed.assign(digits.begin() + static_cast<std::ptrdiff_t>(i), digits.end());
        return trimmed;
    }
}

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t output_base)
{
    if ((input_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("input base must be >= 2");
    } else {
        // continue
    }

    if ((output_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("output base must be >= 2");
    } else {
        // continue
    }

    for (std::size_t idx{0U}; idx < digits.size(); ++idx) {
        if ((digits[idx] >= input_base)) {
            throw std::invalid_argument("digit out of range for input base");
        } else {
            // ok
        }
    }

    if (digits.empty()) {
        return std::vector<std::uint32_t>{};
    } else {
        // continue
    }

    std::vector<std::uint32_t> src{trim_leading_zeros(digits)};
    if ((src.size() == static_cast<std::size_t>(1U)) && (src[0] == static_cast<std::uint32_t>(0U))) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    } else {
        // continue
    }

    std::vector<std::uint32_t> result{};

    while (!src.empty()) {
        std::vector<std::uint32_t> quotient{};
        quotient.reserve(src.size());

        std::uint64_t remainder{0ULL};

        for (std::size_t i{0U}; i < src.size(); ++i) {
            const std::uint64_t value{
                (remainder * static_cast<std::uint64_t>(input_base)) +
                static_cast<std::uint64_t>(src[i])
            };

            const std::uint64_t q64{value / static_cast<std::uint64_t>(output_base)};
            const std::uint64_t r64{value % static_cast<std::uint64_t>(output_base)};

            if (q64 > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max())) {
                throw std::overflow_error("quotient digit does not fit in 32 bits");
            } else {
                // ok
            }
            const std::uint32_t q32{static_cast<std::uint32_t>(q64)};
            if ((q32 != static_cast<std::uint32_t>(0U)) || (!quotient.empty())) {
                quotient.push_back(q32);
            } else {
                // skip leading zero in quotient
            }
            remainder = r64;
        }

        if (remainder > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max())) {
            throw std::overflow_error("remainder digit does not fit in 32 bits");
        } else {
            // ok
        }
        result.push_back(static_cast<std::uint32_t>(remainder));
        src = quotient;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
