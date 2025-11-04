#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n < 1) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    if (n == 1) {
        return deficient;
    }

    long long sum = 1;
    for (int i = 2; 1LL * i * i <= n; ++i) {
        if (n % i == 0) {
            int j = n / i;
            sum += i;
            if (j != i) {
                sum += j;
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
