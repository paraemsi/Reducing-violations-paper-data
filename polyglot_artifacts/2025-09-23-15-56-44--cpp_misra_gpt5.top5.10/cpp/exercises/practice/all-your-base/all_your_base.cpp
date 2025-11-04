#include "all_your_base.h"

#include <stdexcept>
#include <cstddef>
#include <limits>

namespace all_your_base {

auto convert(std::uint32_t in_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t out_base) -> std::vector<std::uint32_t>
{
    if ((in_base < 2U) || (out_base < 2U)) {
        throw std::invalid_argument("bases must be >= 2");
    }

    // Validate digits and trim leading zeros index
    std::size_t first_non_zero = 0U;
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        if (digits[i] >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if ((first_non_zero == i) && (digits[i] == 0U)) {
            ++first_non_zero;
        }
    }

    // If no digits or all zeros -> represents zero
    if ((digits.empty()) || (first_non_zero == digits.size())) {
        return std::vector<std::uint32_t>{};
    }

    // Working copy widened to 64-bit to avoid overflow and narrowing
    std::vector<std::uint64_t> src;
    src.reserve(digits.size() - first_non_zero);
    for (std::size_t i = first_non_zero; i < digits.size(); ++i) {
        src.push_back(static_cast<std::uint64_t>(digits[i]));
    }

    // Collect remainders (least-significant first)
    std::vector<std::uint64_t> remainders;

    while (!src.empty()) {
        std::vector<std::uint64_t> quotient;
        quotient.reserve(src.size());

        std::uint64_t carry = 0ULL;
        const std::uint64_t in_base_64 = static_cast<std::uint64_t>(in_base);
        const std::uint64_t out_base_64 = static_cast<std::uint64_t>(out_base);

        for (std::size_t i = 0U; i < src.size(); ++i) {
            const std::uint64_t accum = (carry * in_base_64) + src[i];
            const std::uint64_t q_digit = (accum / out_base_64);
            carry = (accum % out_base_64);
            quotient.push_back(q_digit);
        }

        // Push remainder from this division step
        remainders.push_back(carry);

        // Trim leading zeros from quotient for next iteration
        std::size_t q_first_nz = 0U;
        for (std::size_t i = 0U; i < quotient.size(); ++i) {
            if (quotient[i] != 0ULL) {
                q_first_nz = i;
                break;
            } else {
                // If all are zeros, q_first_nz will end at 0 but we handle below
                if ((i + 1U) == quotient.size()) {
                    q_first_nz = quotient.size();
                }
            }
        }

        if (q_first_nz >= quotient.size()) {
            src.clear();
        } else {
            std::vector<std::uint64_t> next;
            next.reserve(quotient.size() - q_first_nz);
            for (std::size_t i = q_first_nz; i < quotient.size(); ++i) {
                next.push_back(quotient[i]);
            }
            src = next;
        }
    }

    // Reverse remainders to get most-significant first
    std::vector<std::uint32_t> result;
    result.reserve(remainders.size());
    for (std::size_t i = 0U; i < remainders.size(); ++i) {
        const std::size_t idx = (remainders.size() - 1U) - i;
        const std::uint64_t val64 = remainders[idx];
        if (val64 > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max())) {
            throw std::overflow_error("digit exceeds uint32_t range");
        }
        result.push_back(static_cast<std::uint32_t>(val64));
    }

    // Edge-case: zero produces an empty digit list
    if (result.empty()) {
        return std::vector<std::uint32_t>{};
    }

    return result;
}

}  // namespace all_your_base
