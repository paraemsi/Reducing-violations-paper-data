#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Only positive integers can be classified");
    }
    if (n == 1) {
        return deficient;
    }

    int sum = 1;
    for (int i = 2; i <= n / i; ++i) {
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
