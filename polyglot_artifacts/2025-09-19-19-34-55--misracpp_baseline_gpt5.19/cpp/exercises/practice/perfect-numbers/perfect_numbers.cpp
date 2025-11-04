#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

namespace {
int aliquot_sum(int n) {
    if (n == 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) {
                sum += other;
            }
        }
    }
    return sum;
}
}  // namespace

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error(
            "Classification is only possible for positive integers.");
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
