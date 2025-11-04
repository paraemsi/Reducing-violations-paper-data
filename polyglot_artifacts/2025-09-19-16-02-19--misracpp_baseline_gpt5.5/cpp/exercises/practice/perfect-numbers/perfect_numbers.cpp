#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Classification is only defined for positive integers.");
    }
    if (n == 1) {
        return classification::deficient;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int q = n / i;
            if (q != i) {
                sum += q;
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
