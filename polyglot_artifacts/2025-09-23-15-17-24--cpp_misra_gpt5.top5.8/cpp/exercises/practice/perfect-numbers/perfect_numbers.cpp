#include "perfect_numbers.h"

#include <stdexcept>

namespace
{
    auto aliquot_sum(std::uint64_t n) -> std::uint64_t
    {
        std::uint64_t sum = static_cast<std::uint64_t>(0);

        if ((n > static_cast<std::uint64_t>(1))) {
            sum = static_cast<std::uint64_t>(1);

            for (std::uint64_t i = static_cast<std::uint64_t>(2); (i <= (n / i)); ++i) {
                if (((n % i) == static_cast<std::uint64_t>(0))) {
                    const std::uint64_t d = n / i;
                    sum += i;

                    if ((d != i)) {
                        sum += d;
                    }
                }
            }
        }

        return sum;
    }
}  // unnamed namespace

namespace perfect_numbers {

auto classify(std::int64_t n) -> classification
{
    if ((n <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("classification is undefined for non-natural numbers");
    }

    const std::uint64_t pos = static_cast<std::uint64_t>(n);
    const std::uint64_t sum = aliquot_sum(pos);

    if ((sum == pos)) {
        return classification::perfect;
    } else if ((sum > pos)) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
