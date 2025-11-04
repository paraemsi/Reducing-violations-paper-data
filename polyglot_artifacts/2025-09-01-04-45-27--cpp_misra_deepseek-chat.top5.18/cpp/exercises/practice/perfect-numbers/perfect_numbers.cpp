#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace perfect_numbers {
    classification classify(std::int32_t num) {
        if (num <= 0) {
            throw std::domain_error("Classification is only possible for positive integers.");
        }
        
        // Calculate the sum of proper divisors
        std::int32_t sum = 0;
        for (std::int32_t i = 1; i <= (num / 2); i++) {
            if ((num % i) == 0) {
                sum += i;
            }
        }
        
        // Compare the sum to the number to determine classification
        if (sum == num) {
            return classification::perfect;
        } else if (sum > num) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}  // namespace perfect_numbers
