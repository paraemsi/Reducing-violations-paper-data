#if !defined(ZEBRA_PUZZLE_H)
#define ZEBRA_PUZZLE_H

#include <cstdint>
#include <string>

namespace zebra_puzzle {

enum class Color : std::uint8_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet : std::uint8_t { Dog, Snail, Fox, Horse, Zebra };
enum class Drink : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : std::uint8_t { Dancing, Painting, Reading, Football, Chess };

struct Solution {
    std::string drinksWater;
    std::string ownsZebra;
};

Solution solve();

}  // namespace zebra_puzzle

#endif  // ZEBRA_PUZZLE_H
