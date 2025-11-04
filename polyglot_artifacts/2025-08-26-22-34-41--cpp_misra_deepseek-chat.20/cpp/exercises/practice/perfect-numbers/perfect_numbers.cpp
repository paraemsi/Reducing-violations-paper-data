#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(std::int64_t number) {
    if (number <= 0) {
        throw std::domain_error("Classification is only defined for positive integers");
    }
    
    if (number == 1) {
        return classification::deficient;
    }
    
    std::int64_t sum = 1;
    // To avoid floating point inaccuracies, we can use integer square root
    // We'll find the largest integer where i*i <= number
    std::int64_t i = 2;
    while (i * i <= number) {
        if (number % i == 0) {
            sum += i;
            std::int64_t complement = number / i;
            if (complement != i) {
                sum += complement;
            }
        }
        ++i;
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
