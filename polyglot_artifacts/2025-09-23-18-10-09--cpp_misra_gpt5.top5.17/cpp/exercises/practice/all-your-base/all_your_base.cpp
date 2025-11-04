#include "all_your_base.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

auto convert(unsigned int in_base, const std::vector<unsigned int>& digits, unsigned int out_base) -> std::vector<unsigned int>
{
    if ((in_base < 2U) || (out_base < 2U)) {
        throw std::invalid_argument("base must be >= 2");
    }

    for (const unsigned int d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Remove leading zeros
    std::size_t first_non_zero = 0U;
    while ((first_non_zero < digits.size()) && (digits[first_non_zero] == 0U)) {
        first_non_zero = static_cast<std::size_t>(first_non_zero + static_cast<std::size_t>(1U));
    }

    if (first_non_zero == digits.size()) {
        return std::vector<unsigned int>{};
    }

    std::vector<unsigned int> source;
    source.reserve(static_cast<std::size_t>(digits.size() - first_non_zero));
    for (std::size_t i = first_non_zero; i < digits.size(); i = static_cast<std::size_t>(i + static_cast<std::size_t>(1U))) {
        source.push_back(digits[i]);
    }

    std::vector<unsigned int> result;

    // Repeated division algorithm to convert bases
    while (!source.empty()) {
        std::vector<unsigned int> next;
        next.reserve(source.size());

        std::uint64_t remainder = 0U;

        for (const unsigned int d : source) {
            const std::uint64_t acc =
                (remainder * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(d);
            const std::uint64_t q64 = acc / static_cast<std::uint64_t>(out_base);
            remainder = acc % static_cast<std::uint64_t>(out_base);

            const unsigned int q = static_cast<unsigned int>(q64);
            if ((q != 0U) || (!next.empty())) {
                next.push_back(q);
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        source.swap(next);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
