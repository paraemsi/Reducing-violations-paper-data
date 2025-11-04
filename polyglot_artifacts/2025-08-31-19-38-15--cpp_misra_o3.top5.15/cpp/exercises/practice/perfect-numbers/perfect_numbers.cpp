#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

namespace
{

auto aliquot_sum(std::uint32_t number) -> std::uint32_t
{
    if (number <= static_cast<std::uint32_t>(1))
    {
        return static_cast<std::uint32_t>(0);
    }

    std::uint32_t sum {static_cast<std::uint32_t>(1)};

    for (std::uint32_t divisor {static_cast<std::uint32_t>(2)};
         (static_cast<std::uint64_t>(divisor) * static_cast<std::uint64_t>(divisor)) <= static_cast<std::uint64_t>(number);
         ++divisor)
    {
        if ((number % divisor) == static_cast<std::uint32_t>(0))
        {
            const std::uint32_t complement {number / divisor};

            sum += divisor;

            if (complement != divisor)
            {
                sum += complement;
            }
        }
    }

    return sum;
}

}  // unnamed namespace

[[nodiscard]] auto classify(std::uint32_t number) -> classification
{
    if (number == static_cast<std::uint32_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const std::uint32_t sum {aliquot_sum(number)};

    if (sum == number)
    {
        return classification::perfect;
    }
    else if (sum > number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

[[nodiscard]] auto classify(std::int32_t number) -> classification
{
    if (number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    /* MISRA C++: conversion from signed to unsigned is deliberate and justified
       because the algorithm operates on positive magnitudes only. */
    return classify(static_cast<std::uint32_t>(number));
}

}  // namespace perfect_numbers
