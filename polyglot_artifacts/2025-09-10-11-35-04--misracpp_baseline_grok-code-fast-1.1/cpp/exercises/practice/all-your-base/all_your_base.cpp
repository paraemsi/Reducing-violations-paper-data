#include "all_your_base.h"
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base, const std::vector<unsigned int>& digits, int output_base) {
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be at least 2");
    }
    if (digits.empty()) {
        return {0};
    }
    // Convert to decimal
    unsigned long long decimal = 0;
    unsigned long long power = 1;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        if (digits[i] >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("Invalid digit");
        }
        decimal += static_cast<unsigned long long>(digits[i]) * power;
        power *= input_base;
    }
    // Now convert decimal to output_base
    std::vector<unsigned int> result;
    if (decimal == 0) {
        return {0};
    }
    while (decimal > 0) {
        result.push_back(decimal % output_base);
        decimal /= output_base;
    }
    // Reverse because we built it backwards
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
