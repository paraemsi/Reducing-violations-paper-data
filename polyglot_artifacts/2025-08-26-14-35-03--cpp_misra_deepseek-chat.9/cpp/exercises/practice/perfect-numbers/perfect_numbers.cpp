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
    
    std::int64_t sum = 1;
    for (std::int64_t i = 2; i <= (number / i); ++i) {
        if ((number % i) == 0) {
            sum += i;
            std::int64_t other_divisor = number / i;
            if (other_divisor != i) {
                sum += other_divisor;
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
