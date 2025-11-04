#include "perfect_numbers.h"
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n < 1) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    if (n == 1) {
        return classification::deficient;
    }

    int sum = 1;
    int limit = static_cast<int>(std::sqrt(n));
    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {
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
