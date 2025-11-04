#include "perfect_numbers.h"

#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

namespace {

// Helper to compute the aliquot sum of a positive integer.
int aliquot_sum(int n) {
    int sum = 1;  // 1 is a proper divisor of every n > 1
    int limit = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            int complement = n / i;
            if (complement != i) {
                sum += complement;
            }
        }
    }
    return (n == 1) ? 0 : sum;  // 1 has no proper divisors
}

}  // namespace

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only defined for positive integers");
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
