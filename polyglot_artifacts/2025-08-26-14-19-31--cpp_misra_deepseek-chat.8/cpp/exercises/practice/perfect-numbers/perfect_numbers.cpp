#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {
    classification classify(number_t num) {
        if (num == 0) {
            throw std::domain_error("Classification is only possible for positive integers.");
        }
        
        // To prevent overflow, use a 64-bit unsigned integer for the sum
        // Since number_t is an alias for std::uint32_t, we need to be consistent
        // Let's create another alias for the sum type to ensure it's larger
        using sum_t = std::uint64_t;
        
        sum_t sum = 0;
        
        // Find all proper divisors and sum them
        for (number_t i = 1; i <= (num / 2); i++) {
            if ((num % i) == 0) {
                sum += static_cast<sum_t>(i);
            }
        }
        
        // Compare the sum to the original number
        // Cast num to sum_t to ensure proper comparison
        if (sum == static_cast<sum_t>(num)) {
            return classification::perfect;
        } else if (sum > static_cast<sum_t>(num)) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}  // namespace perfect_numbers
