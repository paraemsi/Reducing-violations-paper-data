#include "perfect_numbers.h"

#include <cmath>
#include <stdexcept>

namespace perfect_numbers {

static int aliquot_sum(int n) {
    if (n == 1) {
        return 0;  // 1 has no proper divisors other than itself
    }

    int sum = 1;  // 1 is a proper divisor of every number > 1
    int limit = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            int complement = n / i;
            sum += i;
            if (complement != i) {  // avoid double-counting square roots
                sum += complement;
            }
        }
    }
    return sum;
}

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
