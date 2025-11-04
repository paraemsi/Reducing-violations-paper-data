#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

// House attributes
enum class Color : std::uint8_t { Red, Green, Ivory, Yellow, Blue, Count };
enum class Nationality : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese, Count };
enum class Pet : std::uint8_t { Dog, Snails, Fox, Horse, Zebra, Count };
enum class Drink : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water, Count };
enum class Hobby : std::uint8_t { Reading, Dancing, Painting, Football, Chess, Count };

// For MISRA: use aliases for index type
using house_index_t = std::uint8_t;
constexpr house_index_t HOUSE_COUNT = static_cast<house_index_t>(5U);

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

namespace {

template<typename T>
using Perm = std::array<T, HOUSE_COUNT>;

template<typename T>
void fill_permutation(Perm<T>& arr, std::array<T, HOUSE_COUNT> vals) {
    for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
        arr[i] = vals[i];
    }
}

template<typename T>
bool is_unique(const Perm<T>& arr) {
    for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
        for (house_index_t j = static_cast<house_index_t>(i + 1U); j < HOUSE_COUNT; ++j) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

} // namespace

Solution solve() {
    // All possible values for each attribute
    std::array<Color, HOUSE_COUNT> colors = { Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue };
    std::array<Nationality, HOUSE_COUNT> nationalities = { Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese };
    std::array<Pet, HOUSE_COUNT> pets = { Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra };
    std::array<Drink, HOUSE_COUNT> drinks = { Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water };
    std::array<Hobby, HOUSE_COUNT> hobbies = { Hobby::Reading, Hobby::Dancing, Hobby::Painting, Hobby::Football, Hobby::Chess };

    // Removed unused permutation variables to fix compiler warnings

    // For performance, fix clues with absolute positions first
    // 9. The person in the middle house drinks milk.
    // 10. The Norwegian lives in the first house.
    // 15. The Norwegian lives next to the blue house.

    // Generate all permutations for each attribute
    std::sort(colors.begin(), colors.end());
    std::sort(nationalities.begin(), nationalities.end());
    std::sort(pets.begin(), pets.end());
    std::sort(drinks.begin(), drinks.end());
    std::sort(hobbies.begin(), hobbies.end());

    do {
        // 6. The green house is immediately to the right of the ivory house.
        house_index_t green_idx = 0U;
        house_index_t ivory_idx = 0U;
        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
            if (colors[i] == Color::Green) { green_idx = i; }
            if (colors[i] == Color::Ivory) { ivory_idx = i; }
        }
        if (green_idx != (ivory_idx + 1U)) { continue; }

        // 15. The Norwegian lives next to the blue house.
        house_index_t blue_idx = 0U;
        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
            if (colors[i] == Color::Blue) { blue_idx = i; }
        }

        do {
            // 10. The Norwegian lives in the first house.
            house_index_t norwegian_idx = 0U;
            for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                if (nationalities[i] == Nationality::Norwegian) { norwegian_idx = i; }
            }
            if (norwegian_idx != 0U) { continue; }
            // 15. The Norwegian lives next to the blue house.
            if (!((blue_idx == (norwegian_idx + 1U)) || (norwegian_idx == (blue_idx + 1U)))) { continue; }

            do {
                // 9. The person in the middle house drinks milk.
                if (drinks[2U] != Drink::Milk) { continue; }

                do {
                    do {
                        // Now check all clues
                        bool valid = true;

                        // 2. The Englishman lives in the red house.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((nationalities[i] == Nationality::Englishman) && (colors[i] != Color::Red)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 3. The Spaniard owns the dog.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((nationalities[i] == Nationality::Spaniard) && (pets[i] != Pet::Dog)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 4. The person in the green house drinks coffee.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((colors[i] == Color::Green) && (drinks[i] != Drink::Coffee)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 5. The Ukrainian drinks tea.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((nationalities[i] == Nationality::Ukrainian) && (drinks[i] != Drink::Tea)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 7. The snail owner likes to go dancing.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((pets[i] == Pet::Snails) && (hobbies[i] != Hobby::Dancing)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 8. The person in the yellow house is a painter.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((colors[i] == Color::Yellow) && (hobbies[i] != Hobby::Painting)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if (hobbies[i] == Hobby::Reading) {
                                bool found = false;
                                if ((i > 0U) && (pets[i - 1U] == Pet::Fox)) { found = true; }
                                if ((i < (HOUSE_COUNT - 1U)) && (pets[i + 1U] == Pet::Fox)) { found = true; }
                                if (!found) { valid = false; break; }
                            }
                        }
                        if (!valid) { continue; }

                        // 12. The painter's house is next to the house with the horse.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if (hobbies[i] == Hobby::Painting) {
                                bool found = false;
                                if ((i > 0U) && (pets[i - 1U] == Pet::Horse)) { found = true; }
                                if ((i < (HOUSE_COUNT - 1U)) && (pets[i + 1U] == Pet::Horse)) { found = true; }
                                if (!found) { valid = false; break; }
                            }
                        }
                        if (!valid) { continue; }

                        // 13. The person who plays football drinks orange juice.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((hobbies[i] == Hobby::Football) && (drinks[i] != Drink::OrangeJuice)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 14. The Japanese person plays chess.
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if ((nationalities[i] == Nationality::Japanese) && (hobbies[i] != Hobby::Chess)) { valid = false; break; }
                        }
                        if (!valid) { continue; }

                        // 1. There are five houses. (already enforced)
                        // 15. The Norwegian lives next to the blue house. (already enforced above)

                        // All constraints satisfied, extract solution
                        std::string drinksWater;
                        std::string ownsZebra;
                        for (house_index_t i = 0U; i < HOUSE_COUNT; ++i) {
                            if (drinks[i] == Drink::Water) {
                                switch (nationalities[i]) {
                                    case Nationality::Englishman: drinksWater = "Englishman"; break;
                                    case Nationality::Spaniard: drinksWater = "Spaniard"; break;
                                    case Nationality::Ukrainian: drinksWater = "Ukrainian"; break;
                                    case Nationality::Norwegian: drinksWater = "Norwegian"; break;
                                    case Nationality::Japanese: drinksWater = "Japanese"; break;
                                    default: drinksWater = ""; break;
                                }
                            }
                            if (pets[i] == Pet::Zebra) {
                                switch (nationalities[i]) {
                                    case Nationality::Englishman: ownsZebra = "Englishman"; break;
                                    case Nationality::Spaniard: ownsZebra = "Spaniard"; break;
                                    case Nationality::Ukrainian: ownsZebra = "Ukrainian"; break;
                                    case Nationality::Norwegian: ownsZebra = "Norwegian"; break;
                                    case Nationality::Japanese: ownsZebra = "Japanese"; break;
                                    default: ownsZebra = ""; break;
                                }
                            }
                        }
                        return Solution{drinksWater, ownsZebra};

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(drinks.begin(), drinks.end()));
            } while (std::next_permutation(pets.begin(), pets.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // If no solution found (should not happen)
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
