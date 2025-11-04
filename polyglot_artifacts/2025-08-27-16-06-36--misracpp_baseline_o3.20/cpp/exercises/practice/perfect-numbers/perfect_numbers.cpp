#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    // Aliquot sum calculation
    if (n == 1) {
        return classification::deficient; // aliquot sum of 1 is 0
    }

    int sum = 1; // 1 is always a proper divisor of n > 1
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) { // avoid double-counting squares
                sum += other;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    } else if (sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
