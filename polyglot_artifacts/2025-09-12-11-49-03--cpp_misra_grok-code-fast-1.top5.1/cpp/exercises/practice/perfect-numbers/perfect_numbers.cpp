#include "perfect_numbers.h"

#include <cstdint>

namespace perfect_numbers {
    std::int64_t aliquot_sum(std::int32_t n) {
        if (n <= 0) {
            return 0;
        }
        std::int64_t sum = 0;
        for (std::int32_t i = 1; i <= (n / i); ++i) {
            if ((n % i) == 0) {
                if (i < n) {
                    sum += i;
                }
                if (((n / i) < n) && ((n / i) > i)) {
                    sum += (n / i);
                }
            }
        }
        return sum;
    }

    classification classify(std::int32_t number) {
        if (number <= 0) {
            return classification::deficient;
        }
        std::int64_t sum = aliquot_sum(number);
        if (sum == number) {
            return classification::perfect;
        } else if (sum > number) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}  // namespace perfect_numbers
