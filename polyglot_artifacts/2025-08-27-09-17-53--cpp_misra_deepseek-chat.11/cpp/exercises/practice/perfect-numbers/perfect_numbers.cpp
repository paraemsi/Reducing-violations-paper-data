#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    if (number == 1) {
        return classification::deficient;
    }
    
    // Start sum at 1 since 1 is always a proper divisor for numbers > 1
    std::int64_t sum = 1;
    std::int64_t sqrt_number = static_cast<std::int64_t>(std::sqrt(number));
    
    for (std::int64_t i = 2; i <= sqrt_number; i++) {
        if ((number % i) == 0) {
            sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                sum += complement;
            }
        }
    }
    
    // Classify based on the sum
    if (sum == number) {
        return classification::perfect;
    } else if (sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
