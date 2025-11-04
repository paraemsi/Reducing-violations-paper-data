#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    if (num == 1) {
        return classification::deficient;
    }
    
    int sum = 1; // 1 is always a proper divisor for numbers > 1
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            int other = num / i;
            if (other != i) {
                sum += other;
            }
        }
    }
    
    // Determine the classification
    if (sum == num) {
        return classification::perfect;
    } else if (sum > num) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
