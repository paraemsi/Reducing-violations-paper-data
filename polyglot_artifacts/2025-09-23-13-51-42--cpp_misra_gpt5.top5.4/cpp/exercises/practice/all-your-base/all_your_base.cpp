#include "all_your_base.h"

#include <algorithm>
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<digit_t> convert(base_t in_base, const std::vector<digit_t>& digits, base_t out_base)
{
    // Validate bases
    if ((in_base < static_cast<base_t>(2U)) || (out_base < static_cast<base_t>(2U))) {
        throw std::invalid_argument("invalid base");
    }

    // Validate digits presence
    if (digits.empty()) {
        return std::vector<digit_t>{};
    }

    // Validate digit values and detect all-zero input
    bool all_zero = true;
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        const digit_t d = digits[i];
        if ((d >= in_base)) {
            throw std::invalid_argument("invalid digit");
        }
        if (d != static_cast<digit_t>(0U)) {
            all_zero = false;
        }
    }

    if (all_zero) {
        return std::vector<digit_t>{};
    }

    // Accumulator in least-significant-first order, in base 'out_base'
    std::vector<digit_t> acc;
    acc.push_back(static_cast<digit_t>(0U));

    for (std::size_t idx = 0U; idx < digits.size(); ++idx) {
        const digit_t d = digits[idx];

        // acc = acc * in_base (in base out_base)
        std::uint64_t carry_mul = static_cast<std::uint64_t>(0U);
        for (std::size_t i = 0U; i < acc.size(); ++i) {
            const std::uint64_t prod = (static_cast<std::uint64_t>(acc[i]) * static_cast<std::uint64_t>(in_base));
            const std::uint64_t with_carry = (prod + carry_mul);
            acc[i] = static_cast<digit_t>(with_carry % static_cast<std::uint64_t>(out_base));
            carry_mul = (with_carry / static_cast<std::uint64_t>(out_base));
        }
        while (carry_mul > static_cast<std::uint64_t>(0U)) {
            const std::uint64_t chunk = (carry_mul % static_cast<std::uint64_t>(out_base));
            acc.push_back(static_cast<digit_t>(chunk));
            carry_mul = (carry_mul / static_cast<std::uint64_t>(out_base));
        }

        // acc = acc + d (still in base out_base)
        std::uint64_t carry_add = static_cast<std::uint64_t>(d);
        std::size_t i = 0U;
        while (i < acc.size()) {
            const std::uint64_t sum = (static_cast<std::uint64_t>(acc[i]) + carry_add);
            acc[i] = static_cast<digit_t>(sum % static_cast<std::uint64_t>(out_base));
            carry_add = (sum / static_cast<std::uint64_t>(out_base));
            ++i;
        }
        while (carry_add > static_cast<std::uint64_t>(0U)) {
            const std::uint64_t chunk = (carry_add % static_cast<std::uint64_t>(out_base));
            acc.push_back(static_cast<digit_t>(chunk));
            carry_add = (carry_add / static_cast<std::uint64_t>(out_base));
        }
    }

    // Convert to most-significant-first order
    std::reverse(acc.begin(), acc.end());

    // Remove any potential leading zeros (should not be present except pathological cases)
    std::size_t first_non_zero = 0U;
    while ((first_non_zero < acc.size()) && (acc[first_non_zero] == static_cast<digit_t>(0U))) {
        ++first_non_zero;
    }
    if (first_non_zero == acc.size()) {
        return std::vector<digit_t>{};
    }

    return std::vector<digit_t>(acc.begin() + static_cast<std::vector<digit_t>::difference_type>(first_non_zero), acc.end());
}

}  // namespace all_your_base
