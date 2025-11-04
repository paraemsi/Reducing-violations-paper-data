#pragma once
#include <array>
#include <cstdint>

namespace yacht {

using Die = std::uint8_t;
using Dice = std::array<Die, 5U>;

// MISRA C++: Use a typedef/using alias for integral types instead of raw std::uint8_t in enum
typedef std::uint8_t CategoryType;

enum class Category : CategoryType
{
    Ones = static_cast<CategoryType>(0U),
    Twos = static_cast<CategoryType>(1U),
    Threes = static_cast<CategoryType>(2U),
    Fours = static_cast<CategoryType>(3U),
    Fives = static_cast<CategoryType>(4U),
    Sixes = static_cast<CategoryType>(5U),
    FullHouse = static_cast<CategoryType>(6U),
    FourOfAKind = static_cast<CategoryType>(7U),
    LittleStraight = static_cast<CategoryType>(8U),
    BigStraight = static_cast<CategoryType>(9U),
    Choice = static_cast<CategoryType>(10U),
    Yacht = static_cast<CategoryType>(11U)
};

auto score(const Dice& dice, Category category) -> std::uint32_t;

// Accept string category for test compatibility
auto score(const Dice& dice, const char* category) -> std::uint32_t;

}  // namespace yacht
