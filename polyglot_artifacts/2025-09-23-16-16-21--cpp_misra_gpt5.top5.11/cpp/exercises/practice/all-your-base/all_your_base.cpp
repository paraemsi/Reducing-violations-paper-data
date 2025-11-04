#include "all_your_base.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace all_your_base {

namespace {

// Remove leading zeros from the digit sequence (most-significant digit first)
inline void trim_leading_zeros(std::vector<Digit>& v)
{
    std::size_t first_non_zero = 0U;
    while ((first_non_zero < v.size()) && (v[first_non_zero] == static_cast<Digit>(0U))) {
        first_non_zero = first_non_zero + 1U;
    }

    if (first_non_zero > 0U) {
        v.erase(
            v.begin(),
            v.begin() + static_cast<std::vector<Digit>::difference_type>(first_non_zero));
    }
}

}  // namespace

std::vector<Digit> convert(Base in_base,
                           const std::vector<Digit>& digits,
                           Base out_base)
{
    if ((in_base < static_cast<Base>(2U)) || (out_base < static_cast<Base>(2U))) {
        throw std::invalid_argument("base must be >= 2");
    }

    // Validate digits and copy to working buffer
    std::vector<Digit> work;
    work.reserve(digits.size());
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        const Digit d = digits[i];
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        work.push_back(d);
    }

    trim_leading_zeros(work);

    if (work.empty()) {
        return std::vector<Digit>(1U, static_cast<Digit>(0U));
    }

    // Repeated division algorithm that avoids constructing a potentially large integer
    std::vector<Digit> out;
    while (!work.empty()) {
        std::vector<Digit> quotient;
        quotient.reserve(work.size());

        std::uint64_t remainder = static_cast<std::uint64_t>(0U);
        for (std::size_t i = 0U; i < work.size(); ++i) {
            const std::uint64_t accumulator =
                (remainder * static_cast<std::uint64_t>(in_base)) +
                static_cast<std::uint64_t>(work[i]);

            const std::uint64_t qdigit64 =
                accumulator / static_cast<std::uint64_t>(out_base);
            const std::uint64_t new_remainder =
                accumulator % static_cast<std::uint64_t>(out_base);

            if (qdigit64 > static_cast<std::uint64_t>(std::numeric_limits<Digit>::max())) {
                throw std::overflow_error("quotient digit overflow");
            }
            quotient.push_back(static_cast<Digit>(qdigit64));
            remainder = new_remainder;
        }

        if (remainder > static_cast<std::uint64_t>(std::numeric_limits<Digit>::max())) {
            throw std::overflow_error("remainder overflow");
        }
        out.push_back(static_cast<Digit>(remainder));

        trim_leading_zeros(quotient);
        work.swap(quotient);
    }

    std::reverse(out.begin(), out.end());
    return out;
}

}  // namespace all_your_base
