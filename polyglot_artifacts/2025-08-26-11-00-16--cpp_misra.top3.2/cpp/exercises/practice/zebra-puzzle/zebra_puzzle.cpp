#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

// Type aliases for MISRA C++ compliance
using index_t = std::uint8_t;
using HouseList = std::array<index_t, 5U>;

// All possible values for each attribute
static const std::array<std::string, 5U> kColors = { "red", "green", "ivory", "yellow", "blue" };
static const std::array<std::string, 5U> kNationalities = { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" };
static const std::array<std::string, 5U> kPets = { "dog", "snails", "fox", "horse", "zebra" };
static const std::array<std::string, 5U> kDrinks = { "coffee", "tea", "milk", "orange juice", "water" };
static const std::array<std::string, 5U> kHobbies = { "dancing", "reading", "painting", "chess", "football" };

// Helper to check if two houses are neighbors
static bool is_neighbor(index_t a, index_t b)
{
    return (a > b) ? ((a - b) == static_cast<index_t>(1)) : ((b - a) == static_cast<index_t>(1));
}

// Helper to check all constraints
static bool is_valid(
    const HouseList& color,
    const HouseList& nationality,
    const HouseList& pet,
    const HouseList& drink,
    const HouseList& hobby)
{
    // 2. The Englishman lives in the red house.
    if (color[nationality[0U]] != 0U) { return false; }
    // 3. The Spaniard owns the dog.
    if (pet[nationality[1U]] != 0U) { return false; }
    // 4. The person in the green house drinks coffee.
    if (drink[color[1U]] != 0U) { return false; }
    // 5. The Ukrainian drinks tea.
    if (drink[nationality[2U]] != 1U) { return false; }
    // 6. The green house is immediately to the right of the ivory house.
    if ((color[1U] != (color[2U] + 1U))) { return false; }
    // 7. The snail owner likes to go dancing.
    if (hobby[pet[1U]] != 0U) { return false; }
    // 8. The person in the yellow house is a painter.
    if (hobby[color[3U]] != 2U) { return false; }
    // 9. The person in the middle house drinks milk.
    if (drink[2U] != 2U) { return false; }
    // 10. The Norwegian lives in the first house.
    if (nationality[3U] != 0U) { return false; }
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    if (!is_neighbor(hobby[1U], pet[2U])) { return false; }
    // 12. The painter's house is next to the house with the horse.
    if (!is_neighbor(hobby[2U], pet[3U])) { return false; }
    // 13. The person who plays football drinks orange juice.
    if (drink[hobby[4U]] != 3U) { return false; }
    // 14. The Japanese person plays chess.
    if (hobby[nationality[4U]] != 3U) { return false; }
    // 15. The Norwegian lives next to the blue house.
    if (!is_neighbor(nationality[3U], color[4U])) { return false; }
    return true;
}

Solution solve()
{
    // Each attribute is a permutation of 0..4 (indices into the value arrays)
    HouseList color = {0U, 1U, 2U, 3U, 4U};
    HouseList nationality = {0U, 1U, 2U, 3U, 4U};
    HouseList pet = {0U, 1U, 2U, 3U, 4U};
    HouseList drink = {0U, 1U, 2U, 3U, 4U};
    HouseList hobby = {0U, 1U, 2U, 3U, 4U};

    do {
        do {
            do {
                do {
                    do {
                        if (is_valid(color, nationality, pet, drink, hobby)) {
                            // Find who drinks water and who owns the zebra
                            std::string water_drinker;
                            std::string zebra_owner;
                            for (index_t i = 0U; i < 5U; ++i) {
                                if (drink[i] == 4U) {
                                    water_drinker = kNationalities[nationality[i]];
                                }
                                if (pet[i] == 4U) {
                                    zebra_owner = kNationalities[nationality[i]];
                                }
                            }
                            Solution result;
                            result.drinksWater = water_drinker;
                            result.ownsZebra = zebra_owner;
                            return result;
                        }
                    } while (std::next_permutation(hobby.begin(), hobby.end()));
                } while (std::next_permutation(drink.begin(), drink.end()));
            } while (std::next_permutation(pet.begin(), pet.end()));
        } while (std::next_permutation(nationality.begin(), nationality.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // If no solution found
    Solution result;
    result.drinksWater = "";
    result.ownsZebra = "";
    return result;
}

}  // namespace zebra_puzzle
