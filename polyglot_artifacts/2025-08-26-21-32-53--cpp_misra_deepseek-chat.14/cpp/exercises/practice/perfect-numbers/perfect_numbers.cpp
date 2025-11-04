#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 as a special case - its only proper divisor is none, sum is 0 which is less than 1
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t sum = 1; // 1 is always a proper divisor for numbers > 1
    // Find all divisors up to the square root
    for (std::int64_t i = 2; i * i <= number; ++i) {
        if ((number % i) == 0) {
            sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                sum += complement;
            }
        }
    }
    
    // Compare the sum to the number to determine the classification
    if (sum == number) {
        return classification::perfect;
    } else if (sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
