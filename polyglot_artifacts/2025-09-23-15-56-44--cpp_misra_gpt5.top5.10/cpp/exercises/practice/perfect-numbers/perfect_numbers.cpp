#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

namespace {
auto aliquot_sum(std::uint64_t n) -> std::uint64_t
{
    if ((n <= static_cast<std::uint64_t>(1))) {
        return static_cast<std::uint64_t>(0);
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1);
    for (std::uint64_t i = static_cast<std::uint64_t>(2); (i <= (n / i)); ++i) {
        if (((n % i) == static_cast<std::uint64_t>(0))) {
            const std::uint64_t other = (n / i);
            sum = (sum + i);
            if ((other != i)) {
                sum = (sum + other);
            }
        }
    }
    return sum;
}
}  // unnamed namespace

auto classify(std::int64_t n) -> classification
{
    if ((n <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const std::uint64_t un = static_cast<std::uint64_t>(n);
    const std::uint64_t sum = aliquot_sum(un);

    if ((sum == un)) {
        return classification::perfect;
    } else {
        if ((sum > un)) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
