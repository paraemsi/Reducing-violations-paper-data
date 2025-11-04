#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("classification is only possible for natural numbers.");
    }
    if (n == 1) {
        return deficient;
    }

    int sum = 1;
    for (int i = 2; 1LL * i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {
                sum += other;
            }
        }
    }

    if (sum == n) {
        return perfect;
    }
    if (sum > n) {
        return abundant;
    }
    return deficient;
}

}  // namespace perfect_numbers
