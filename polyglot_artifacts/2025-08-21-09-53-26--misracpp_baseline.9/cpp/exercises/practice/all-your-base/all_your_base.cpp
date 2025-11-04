#include "all_your_base.h"

#include <algorithm>
#include <type_traits>

namespace all_your_base {

namespace {
    template <typename T>
    std::vector<unsigned int> convert_impl(int from_base, const std::vector<T>& digits, int to_base) {
        // Validate bases
        if (from_base < 2) {
            throw std::invalid_argument("from_base must be >= 2");
        }
        if (to_base < 2) {
            throw std::invalid_argument("to_base must be >= 2");
        }
        // Validate digits
        if (!digits.empty()) {
            if (std::any_of(digits.begin(), digits.end(), [](T d){ return d < 0; })) {
                throw std::invalid_argument("digits must be non-negative");
            }
            if (digits.front() == 0 && digits.size() > 1) {
                throw std::invalid_argument("digits may not contain leading zeros");
            }
            if (std::any_of(digits.begin(), digits.end(), [from_base](T d){ return d >= from_base; })) {
                throw std::invalid_argument("all digits must be < from_base");
            }
        }

        // Convert input digits to integer value
        unsigned long long value = 0;
        for (T d : digits) {
            value = value * from_base + d;
        }

        // Special case: input is zero
        if (digits.empty()) {
            return {};
        }
        if (value == 0) {
            return {0};
        }

        // Convert integer value to output base
        std::vector<unsigned int> result;
        while (value > 0) {
            result.push_back(static_cast<unsigned int>(value % to_base));
            value /= to_base;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
}

std::vector<unsigned int> convert(int from_base, const std::vector<int>& digits, int to_base) {
    return convert_impl(from_base, digits, to_base);
}

std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    return convert_impl(from_base, digits, to_base);
}

}  // namespace all_your_base
