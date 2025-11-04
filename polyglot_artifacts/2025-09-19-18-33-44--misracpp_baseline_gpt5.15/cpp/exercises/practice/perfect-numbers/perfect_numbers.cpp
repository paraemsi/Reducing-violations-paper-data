#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("classification is only defined for positive integers");
    }
    if (n == 1) {
        return classification::deficient;
    }

    int sum = 1;
    for (int d = 2; 1LL * d * d <= n; ++d) {
        if (n % d == 0) {
            sum += d;
            int other = n / d;
            if (other != d) {
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
