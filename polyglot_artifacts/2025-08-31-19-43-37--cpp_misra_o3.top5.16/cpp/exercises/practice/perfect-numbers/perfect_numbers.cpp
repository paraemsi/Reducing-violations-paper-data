#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(const integer n) {
    // Classification is only defined for positive integers
    if(n <= static_cast<integer>(0)) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    integer aliquot_sum = static_cast<integer>(0);

    if(n > static_cast<integer>(1)) {
        aliquot_sum = static_cast<integer>(1);

        for(integer factor = static_cast<integer>(2);
            ((factor * factor) <= n);
            ++factor) {
            if(((n % factor) == static_cast<integer>(0))) {
                aliquot_sum += factor;

                const integer complementary = n / factor;
                if(complementary != factor) {
                    aliquot_sum += complementary;
                }
            }
        }
    }

    if(aliquot_sum == n) {
        return classification::perfect;
    } else if(aliquot_sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
