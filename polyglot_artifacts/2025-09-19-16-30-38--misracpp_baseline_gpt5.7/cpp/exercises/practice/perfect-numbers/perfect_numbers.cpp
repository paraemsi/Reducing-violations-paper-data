#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    if (n == 1) {
        return deficient;
    }

    long long sum = 1;
    for (int i = 2; i <= n / i; ++i) {
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
