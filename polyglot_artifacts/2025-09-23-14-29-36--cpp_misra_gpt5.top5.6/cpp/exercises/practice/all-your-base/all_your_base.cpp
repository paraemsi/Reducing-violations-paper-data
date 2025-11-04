#include "all_your_base.h"
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t in_base, const std::vector<std::uint32_t>& digits, std::uint32_t out_base) -> std::vector<std::uint32_t> {
    if ((in_base < static_cast<std::uint32_t>(2U)) || (out_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("base must be >= 2");
    }

    if (digits.empty()) {
        return std::vector<std::uint32_t>{};
    }

    // Validate digits and strip leading zeros
    std::vector<std::uint32_t> work;
    work.reserve(digits.size());
    bool seen_non_zero = false;
    for (std::size_t i = 0U; i < digits.size(); ++i) {
        const std::uint32_t d = digits[i];
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if (!seen_non_zero) {
            if (d == static_cast<std::uint32_t>(0U)) {
                // skip leading zeros
            } else {
                seen_non_zero = true;
                work.push_back(d);
            }
        } else {
            work.push_back(d);
        }
    }

    if (!seen_non_zero) {
        return std::vector<std::uint32_t>{};
    }

    // Repeated division algorithm to avoid overflow
    std::vector<std::uint32_t> remainders;
    remainders.reserve(work.size());

    while (!work.empty()) {
        std::vector<std::uint32_t> next;
        next.reserve(work.size());
        std::uint64_t carry = static_cast<std::uint64_t>(0ULL);

        for (std::size_t i = 0U; i < work.size(); ++i) {
            const std::uint64_t acc = (carry * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(work[i]);
            const std::uint64_t q64 = acc / static_cast<std::uint64_t>(out_base);
            const std::uint64_t r64 = acc % static_cast<std::uint64_t>(out_base);

            const std::uint32_t q = static_cast<std::uint32_t>(q64);
            carry = r64;

            if ((!next.empty()) || (q != static_cast<std::uint32_t>(0U))) {
                next.push_back(q);
            } else {
                // omit leading zeros in quotient
            }
        }

        remainders.push_back(static_cast<std::uint32_t>(carry));
        work = next;
    }

    std::vector<std::uint32_t> out;
    out.reserve(remainders.size());
    for (std::size_t i = 0U; i < remainders.size(); ++i) {
        out.push_back(remainders[remainders.size() - static_cast<std::size_t>(1U) - i]);
    }

    return out;
}

}  // namespace all_your_base
