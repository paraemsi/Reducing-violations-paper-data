#include "all_your_base.h"

#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Trim leading zeros
    std::size_t first_non_zero = 0;
    while (first_non_zero < digits.size() && digits[first_non_zero] == 0) {
        ++first_non_zero;
    }
    std::vector<unsigned int> input;
    if (first_non_zero < digits.size()) {
        input.assign(digits.begin() + first_non_zero, digits.end());
    }

    if (input.empty()) {
        return digits.empty() ? std::vector<unsigned int>{} : std::vector<unsigned int>{0};
    }

    // Validate digits
    for (auto d : input) {
        if (d >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    if (from_base == to_base) {
        return input;
    }

    // Accumulate result in little-endian representation of out_base.
    std::vector<unsigned int> acc_le = {0};

    for (auto d : input) {
        // acc_le *= in_base
        std::uint64_t carry = 0;
        for (std::size_t i = 0; i < acc_le.size(); ++i) {
            std::uint64_t t = static_cast<std::uint64_t>(acc_le[i]) * static_cast<std::uint64_t>(from_base) + carry;
            acc_le[i] = static_cast<unsigned int>(t % static_cast<std::uint64_t>(to_base));
            carry = t / static_cast<std::uint64_t>(to_base);
        }
        while (carry > 0) {
            acc_le.push_back(static_cast<unsigned int>(carry % static_cast<std::uint64_t>(to_base)));
            carry /= static_cast<std::uint64_t>(to_base);
        }

        // acc_le += d
        carry = d;
        for (std::size_t i = 0; i < acc_le.size(); ++i) {
            std::uint64_t t = static_cast<std::uint64_t>(acc_le[i]) + carry;
            acc_le[i] = static_cast<unsigned int>(t % static_cast<std::uint64_t>(to_base));
            carry = t / static_cast<std::uint64_t>(to_base);
        }
        while (carry > 0) {
            acc_le.push_back(static_cast<unsigned int>(carry % static_cast<std::uint64_t>(to_base)));
            carry /= static_cast<std::uint64_t>(to_base);
        }
    }

    // Convert to big-endian
    std::vector<unsigned int> result(acc_le.rbegin(), acc_le.rend());
    return result;
}

}  // namespace all_your_base
