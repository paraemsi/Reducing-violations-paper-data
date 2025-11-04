#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

[[nodiscard]] classification classify(std::int64_t n)
{
    if (n <= static_cast<std::int64_t>(0)) {
        throw std::domain_error("Classification is only possible for positive integers.");
    } else {
        const std::int64_t nn{n};
        std::int64_t sum{static_cast<std::int64_t>(0)};

        if (nn > static_cast<std::int64_t>(1)) {
            sum = static_cast<std::int64_t>(1);
            for (std::int64_t i{static_cast<std::int64_t>(2)}; i <= (nn / i); ++i) {
                if ((nn % i) == static_cast<std::int64_t>(0)) {
                    const std::int64_t other{nn / i};
                    sum += i;
                    if (other != i) {
                        sum += other;
                    } else {
                        { }
                    }
                } else {
                    { }
                }
            }
        } else {
            sum = static_cast<std::int64_t>(0);
        }

        if (sum == nn) {
            return classification::perfect;
        } else {
            if (sum > nn) {
                return classification::abundant;
            } else {
                return classification::deficient;
            }
        }
    }
}


}  // namespace perfect_numbers
