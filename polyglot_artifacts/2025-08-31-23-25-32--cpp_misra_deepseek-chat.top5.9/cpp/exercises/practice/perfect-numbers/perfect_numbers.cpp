#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Classification is only for positive integers");
    }
    
    // Handle the case where number is 1 (no proper divisors)
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t sum = 1; // 1 is always a proper divisor for numbers > 1
    for (std::int64_t i = 2; i <= static_cast<std::int64_t>(std::sqrt(number)); i++) {
        if ((number % i) == 0) {
            sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                sum += complement;
            }
        }
    }
    
    if (sum == number) {
        return classification::perfect;
    } else if (sum > number) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
