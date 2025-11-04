#include "all_your_base.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base, const std::vector<unsigned int>& digits, unsigned int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }
    // Validate digits
    bool leading = true;
    for (auto d : digits) {
        if (leading && d == 0) continue;
        leading = false;
        if (d >= from_base) {
            throw std::invalid_argument("All digits must be less than from_base");
        }
    }
    // Remove leading zeros
    auto it = digits.begin();
    while (it != digits.end() && *it == 0) ++it;
    std::vector<unsigned int> clean_digits(it, digits.end());
    if (clean_digits.empty()) {
        // If input is all zeros or empty, output should be empty vector
        return {};
    }
    // Convert to base 10
    unsigned long long value = 0;
    for (auto d : clean_digits) {
        value = value * from_base + d;
    }
    // Convert from base 10 to to_base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(value % to_base);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
