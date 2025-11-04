#include "all_your_base.h"

#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <vector>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t in_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t out_base) {
    if ((in_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if ((out_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("output base must be >= 2");
    }

    if (digits.empty()) {
        return std::vector<std::uint32_t>{};
    }

    // Validate all digits are in range for the input base
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        const std::uint32_t d = digits[i];
        if ((d >= in_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Skip leading zeros
    std::size_t start = 0U;
    while ((start < digits.size()) && (digits[start] == static_cast<std::uint32_t>(0U))) {
        ++start;
    }

    // If all digits were zero, the value is zero; represent as empty sequence
    if ((start >= digits.size())) {
        return std::vector<std::uint32_t>{};
    }

    // Working copy without leading zeros
    std::vector<std::uint32_t> work;
    work.reserve(digits.size() - start);
    for (std::size_t i = start; i < digits.size(); ++i) {
        work.push_back(digits[i]);
    }

    // Repeated division algorithm to avoid overflow
    std::vector<std::uint32_t> result_rev;
    while (!work.empty()) {
        std::vector<std::uint32_t> next;
        next.reserve(work.size());

        std::uint64_t rem = static_cast<std::uint64_t>(0ULL);

        for (std::size_t i = 0U; i < work.size(); ++i) {
            const std::uint64_t acc = (rem * static_cast<std::uint64_t>(in_base))
                                    + static_cast<std::uint64_t>(work[i]);
            const std::uint64_t q = (acc / static_cast<std::uint64_t>(out_base));
            rem = (acc % static_cast<std::uint64_t>(out_base));

            if ((!next.empty()) || (q != static_cast<std::uint64_t>(0ULL))) {
                next.push_back(static_cast<std::uint32_t>(q));
            }
        }

        result_rev.push_back(static_cast<std::uint32_t>(rem));
        work.swap(next);
    }

    std::reverse(result_rev.begin(), result_rev.end());
    return result_rev;
}

}  // namespace all_your_base
