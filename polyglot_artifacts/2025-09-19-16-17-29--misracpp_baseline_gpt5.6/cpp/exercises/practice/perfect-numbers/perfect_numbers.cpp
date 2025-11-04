#include "perfect_numbers.h"

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("classification is only possible for natural numbers.");
    }

    if (n == 1) {
        return deficient;  // aliquot sum of 1 is 0
    }

    int sum = 1;  // start with 1 as a proper divisor for n > 1

    for (int d = 2; d <= n / d; ++d) {  // iterate up to sqrt(n)
        if (n % d == 0) {
            sum += d;
            int q = n / d;
            if (q != d) {
                sum += q;  // add the complementary divisor
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
