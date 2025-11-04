#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    // Handle 1 separately
    if (num == 1) {
        return classification::deficient;
    }
    
    int aliquot_sum = 1; // 1 is always a divisor
    for (int i = 2; i <= std::sqrt(num); i++) {
        if (num % i == 0) {
            int other = num / i;
            if (i == other) {
                aliquot_sum += i;
            } else {
                aliquot_sum += i + other;
            }
        }
    }
    
    if (aliquot_sum == num) {
        return classification::perfect;
    } else if (aliquot_sum > num) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
