#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    int sum = 0;

    // Compute the aliquot sum by iterating up to sqrt(n) (implicit via i*i <= n)
    for (int i = 1; i * static_cast<long long>(i) <= n; ++i) {
        if (n % i == 0) {
            int quotient = n / i;

            if (i != n) {
                sum += i;  // i is a proper divisor
            }

            // Add the complementary divisor if it's distinct and not the number itself
            if (quotient != i && quotient != n) {
                sum += quotient;
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
