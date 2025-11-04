#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle the case where number is 1 (no proper divisors except itself which we exclude)
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t sum = 0;
    // Find all divisors up to the square root
    for (std::int64_t i = 1; i <= static_cast<std::int64_t>(std::sqrt(number)); ++i) {
        if ((number % i) == 0) {
            // Add the divisor
            if (i != number) {
                sum += i;
            }
            // Add the complement if it's different from i and not equal to number
            std::int64_t complement = number / i;
            if ((complement != i) && (complement != number)) {
                sum += complement;
            }
        }
    }
    
    // Compare the sum to the number
    if (sum == number) {
        return classification::perfect;
    } else if (sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
