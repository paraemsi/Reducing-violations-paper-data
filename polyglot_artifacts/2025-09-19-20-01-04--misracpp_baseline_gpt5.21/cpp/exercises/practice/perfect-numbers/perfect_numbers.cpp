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

    int sum = 1;  // 1 is a proper divisor of every n > 1
    for (int i = 2; 1LL * i * i <= n; ++i) {
        if (n % i == 0) {
            int other = n / i;
            sum += i;
            if (other != i) {
                sum += other;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    } else if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
