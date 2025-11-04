#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace perfect_numbers {

classification classify(std::int32_t num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 separately
    if (num == 1) {
        return classification::deficient;
    }
    
    std::int32_t sum = 1; // 1 is always a proper divisor
    // To avoid floating point issues, we can use i * i <= num
    for (std::int32_t i = 2; (i * i) <= num; ++i) {
        if ((num % i) == 0) {
            sum += i;
            std::int32_t other_divisor = num / i;
            if (other_divisor != i) {
                sum += other_divisor;
            }
        }
    }
    
    // Add parentheses to ensure proper operator precedence
    if (sum == num) {
        return classification::perfect;
    } else {
        if (sum > num) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
