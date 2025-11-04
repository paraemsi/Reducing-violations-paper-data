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
    
    std::int64_t aliquot_sum = 0;
    // Find all proper divisors
    for (std::int64_t i = 1; i <= static_cast<std::int64_t>(std::sqrt(number)); ++i) {
        if ((number % i) == 0) {
            // Add the divisor
            aliquot_sum += i;
            // Add the corresponding divisor
            std::int64_t other_divisor = number / i;
            if ((other_divisor != i) && (other_divisor != number)) {
                aliquot_sum += other_divisor;
            }
        }
    }
    
    // Compare the aliquot sum to the number
    if (aliquot_sum == number) {
        return classification::perfect;
    } else if (aliquot_sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
