#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

namespace {

/**
 * Return the aliquot sum of a positive integer n.
 * Optimized to O(sqrt(n)) by iterating only up to √n and adding factor pairs.
 */
int aliquot_sum(int n) {
    if (n == 1) {
        return 0;          // 1 has no proper divisors
    }

    int sum = 1;           // 1 is a proper divisor of every n > 1
    int limit = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {          // avoid double-counting squares
                sum += other;
            }
        }
    }
    return sum;
}

} // namespace

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    int sum = aliquot_sum(n);

    if (sum == n) {
        return classification::perfect;
    }
    if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
