#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 separately
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t aliquot_sum = 1; // Start with 1 which is always a divisor
    // We can optimize by going up to the square root
    for (std::int64_t i = 2; i <= static_cast<std::int64_t>(std::sqrt(number)); ++i) {
        if ((number % i) == 0) {
            aliquot_sum += i;
            std::int64_t other_divisor = number / i;
            if (other_divisor != i) {
                aliquot_sum += other_divisor;
            }
        }
    }
    
    if (aliquot_sum == number) {
        return classification::perfect;
    } else if (aliquot_sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
