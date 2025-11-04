#include "perfect_numbers.h"

namespace perfect_numbers {

namespace {
int aliquot_sum(int n) {
    if (n <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            int other = n / i;
            sum += i;
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
        throw std::domain_error("Classification is only possible for natural numbers.");
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
