#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (n == 1) {                 // aliquot sum of 1 is 0
        return classification::deficient;
    }

    long long sum = 1;                  // 1 is a proper divisor of every n > 1
    int sqrt_n = static_cast<int>(std::sqrt(static_cast<double>(n)));

    for (int i = 2; i <= sqrt_n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {     // avoid double-counting squares
                sum += other;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    }
    if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
