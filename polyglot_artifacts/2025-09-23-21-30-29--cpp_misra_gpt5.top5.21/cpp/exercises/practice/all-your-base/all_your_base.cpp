#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

static std::vector<std::uint32_t> convert_impl(std::uint32_t from_base,
                                               const std::vector<std::uint32_t>& digits,
                                               std::uint32_t to_base);

std::vector<unsigned int> convert(std::uint32_t from_base,
                                  const std::vector<unsigned int>& digits,
                                  std::uint32_t to_base)
{
    std::vector<std::uint32_t> digits32;
    digits32.reserve(digits.size());
    for (std::size_t i = 0U; (i < digits.size()); ++i) {
        digits32.push_back(static_cast<std::uint32_t>(digits[i]));
    }

    const std::vector<std::uint32_t> out32 = convert_impl(from_base, digits32, to_base);

    std::vector<unsigned int> out;
    out.reserve(out32.size());
    for (std::size_t i = 0U; (i < out32.size()); ++i) {
        out.push_back(static_cast<unsigned int>(out32[i]));
    }
    return out;
}

static std::vector<std::uint32_t> convert_impl(std::uint32_t from_base,
                                               const std::vector<std::uint32_t>& digits,
                                               std::uint32_t to_base)
{
    if ((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        const std::uint32_t d = digits[i];
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Trim leading zeros
    std::size_t first_non_zero = 0U;
    while ((first_non_zero < digits.size()) && (digits[first_non_zero] == static_cast<std::uint32_t>(0U))) {
        ++first_non_zero;
    }

    // All zeros => return single zero
    if (first_non_zero == digits.size()) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    // Working copy of the source number without leading zeros
    std::vector<std::uint32_t> source;
    source.reserve(digits.size() - first_non_zero);
    for (std::size_t i = first_non_zero; i < digits.size(); ++i) {
        source.push_back(digits[i]);
    }

    // Repeated division algorithm: divide by to_base, collect remainders.
    std::vector<std::uint32_t> output_reversed;
    output_reversed.reserve(source.size());

    while (!source.empty()) {
        std::vector<std::uint32_t> quotient;
        quotient.reserve(source.size());

        std::uint64_t carry = static_cast<std::uint64_t>(0U);
        bool have_non_zero = false;

        for (std::size_t i = 0U; i < source.size(); ++i) {
            const std::uint64_t accum =
                (carry * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(source[i]);

            const std::uint32_t qdigit = static_cast<std::uint32_t>(
                accum / static_cast<std::uint64_t>(to_base));  // safe: qdigit < from_base <= UINT32_MAX

            carry = accum % static_cast<std::uint64_t>(to_base);

            if ((qdigit != static_cast<std::uint32_t>(0U)) || have_non_zero) {
                quotient.push_back(qdigit);
                have_non_zero = true;
            }
        }

        // carry fits into uint32_t by construction: carry < to_base <= UINT32_MAX
        output_reversed.push_back(static_cast<std::uint32_t>(carry));
        source.swap(quotient);
    }

    std::reverse(output_reversed.begin(), output_reversed.end());
    return output_reversed;
}

}  // namespace all_your_base
