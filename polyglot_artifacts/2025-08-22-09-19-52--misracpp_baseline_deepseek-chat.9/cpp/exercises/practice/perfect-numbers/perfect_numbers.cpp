#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number must be positive");
    }
    
    int sum = 0;
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            if (i == num) {
                sum += 0; // The number itself is not included
            } else {
                sum += i;
            }
            int other = num / i;
            if (other != i && other != num) {
                sum += other;
            }
        }
    }
    
    if (sum == num) {
        return classification::perfect;
    } else if (sum > num) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
