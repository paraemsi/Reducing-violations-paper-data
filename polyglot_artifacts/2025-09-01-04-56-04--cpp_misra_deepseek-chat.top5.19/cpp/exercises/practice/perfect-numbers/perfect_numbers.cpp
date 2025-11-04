#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>
#include <cstdint>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Classification is only defined for positive integers");
    }
    
    // Handle number == 1 case
    if (number == 1) {
        return classification::deficient;
    }
    
    // Use uint64_t to prevent overflow during summation
    std::uint64_t sum = 1; // 1 is always a divisor
    std::int64_t sqrt_number = static_cast<std::int64_t>(std::sqrt(number));
    
    for (std::int64_t i = 2; i <= sqrt_number; ++i) {
        if ((number % i) == 0) {
            sum += i;
            std::int64_t other_divisor = number / i;
            if (other_divisor != i) {
                sum += other_divisor;
            }
        }
    }
    
    // Compare to determine classification
    if (sum == static_cast<std::uint64_t>(number)) {
        return classification::perfect;
    } else if (sum > static_cast<std::uint64_t>(number)) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
