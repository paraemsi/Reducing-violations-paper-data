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

// For MISRA: use alias for index type
using idx_t = std::uint8_t;
constexpr idx_t kNumHouses = static_cast<idx_t>(5U);

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

namespace {

template <typename T>
constexpr std::array<T, kNumHouses> AllValues() {
    std::array<T, kNumHouses> arr{};
    for(idx_t i = 0U; i < kNumHouses; ++i) {
        arr[i] = static_cast<T>(i);
    }
    return arr;
}

constexpr std::array<Color, kNumHouses> kAllColors = AllValues<Color>();
constexpr std::array<Nationality, kNumHouses> kAllNationalities = AllValues<Nationality>();
constexpr std::array<Pet, kNumHouses> kAllPets = AllValues<Pet>();
constexpr std::array<Drink, kNumHouses> kAllDrinks = AllValues<Drink>();
constexpr std::array<Hobby, kNumHouses> kAllHobbies = AllValues<Hobby>();

// Helper to get string for each attribute
const char* ToString(Nationality n) {
    switch(n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
        default: return "";
    }
}
const char* ToString(Pet p) {
    switch(p) {
        case Pet::Dog: return "dog";
        case Pet::Snails: return "snails";
        case Pet::Fox: return "fox";
        case Pet::Horse: return "horse";
        case Pet::Zebra: return "zebra";
        default: return "";
    }
}
const char* ToString(Drink d) {
    switch(d) {
        case Drink::Coffee: return "coffee";
        case Drink::Tea: return "tea";
        case Drink::Milk: return "milk";
        case Drink::OrangeJuice: return "orange juice";
        case Drink::Water: return "water";
        default: return "";
    }
}
const char* ToString(Color c) {
    switch(c) {
        case Color::Red: return "red";
        case Color::Green: return "green";
        case Color::Ivory: return "ivory";
        case Color::Yellow: return "yellow";
        case Color::Blue: return "blue";
        default: return "";
    }
}
const char* ToString(Hobby h) {
    switch(h) {
        case Hobby::Reading: return "reading";
        case Hobby::Dancing: return "dancing";
        case Hobby::Painting: return "painting";
        case Hobby::Football: return "football";
        case Hobby::Chess: return "chess";
        default: return "";
    }
}

// Check if two houses are neighbors
bool IsNeighbor(idx_t a, idx_t b) {
    return (a + 1U == b) || (b + 1U == a);
}

} // namespace

Solution Solve();

Solution solve() {
    return Solve();
}

Solution Solve() {
    // All permutations for each attribute
    std::array<idx_t, kNumHouses> idxs{};
    for(idx_t i = 0U; i < kNumHouses; ++i) {
        idxs[i] = i;
    }

    // 1. There are five houses. (already modeled)

    // Try all possible permutations for each attribute, but use constraints to prune search.
    // We permute colors, nationalities, pets, drinks, hobbies.
    // We use std::next_permutation, so we need to sort first.
    std::array<Color, kNumHouses> colors = kAllColors;
    do {
        // 6. The green house is immediately to the right of the ivory house.
        idx_t green = 0U, ivory = 0U;
        for(idx_t i = 0U; i < kNumHouses; ++i) {
            if(colors[i] == Color::Green) { green = i; }
            if(colors[i] == Color::Ivory) { ivory = i; }
        }
        if(green != (ivory + 1U)) { continue; }

        std::array<Nationality, kNumHouses> nationalities = kAllNationalities;
        do {
            // 2. The Englishman lives in the red house.
            idx_t englishman = 0U, red = 0U;
            for(idx_t i = 0U; i < kNumHouses; ++i) {
                if(nationalities[i] == Nationality::Englishman) { englishman = i; }
                if(colors[i] == Color::Red) { red = i; }
            }
            if(englishman != red) { continue; }

            // 10. The Norwegian lives in the first house.
            idx_t norwegian = 0U;
            for(idx_t i = 0U; i < kNumHouses; ++i) {
                if(nationalities[i] == Nationality::Norwegian) { norwegian = i; }
            }
            if(norwegian != 0U) { continue; }

            // 15. The Norwegian lives next to the blue house.
            idx_t blue = 0U;
            for(idx_t i = 0U; i < kNumHouses; ++i) {
                if(colors[i] == Color::Blue) { blue = i; }
            }
            if(!IsNeighbor(norwegian, blue)) { continue; }

            std::array<Pet, kNumHouses> pets = kAllPets;
            do {
                // 3. The Spaniard owns the dog.
                idx_t spaniard = 0U, dog = 0U;
                for(idx_t i = 0U; i < kNumHouses; ++i) {
                    if(nationalities[i] == Nationality::Spaniard) { spaniard = i; }
                    if(pets[i] == Pet::Dog) { dog = i; }
                }
                if(spaniard != dog) { continue; }

                std::array<Drink, kNumHouses> drinks = kAllDrinks;
                do {
                    // 4. The person in the green house drinks coffee.
                    if(drinks[green] != Drink::Coffee) { continue; }

                    // 5. The Ukrainian drinks tea.
                    idx_t ukrainian = 0U;
                    for(idx_t i = 0U; i < kNumHouses; ++i) {
                        if(nationalities[i] == Nationality::Ukrainian) { ukrainian = i; }
                    }
                    if(drinks[ukrainian] != Drink::Tea) { continue; }

                    // 9. The person in the middle house drinks milk.
                    if(drinks[2U] != Drink::Milk) { continue; }

                    std::array<Hobby, kNumHouses> hobbies = kAllHobbies;
                    do {
                        // 7. The snail owner likes to go dancing.
                        idx_t snails = 0U, dancing = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(pets[i] == Pet::Snails) { snails = i; }
                            if(hobbies[i] == Hobby::Dancing) { dancing = i; }
                        }
                        if(snails != dancing) { continue; }

                        // 8. The person in the yellow house is a painter.
                        idx_t yellow = 0U, painting = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(colors[i] == Color::Yellow) { yellow = i; }
                            if(hobbies[i] == Hobby::Painting) { painting = i; }
                        }
                        if(yellow != painting) { continue; }

                        // 12. The painter's house is next to the house with the horse.
                        idx_t horse = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(pets[i] == Pet::Horse) { horse = i; }
                        }
                        if(!IsNeighbor(painting, horse)) { continue; }

                        // 13. The person who plays football drinks orange juice.
                        idx_t football = 0U, orangeJuice = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(hobbies[i] == Hobby::Football) { football = i; }
                            if(drinks[i] == Drink::OrangeJuice) { orangeJuice = i; }
                        }
                        if(football != orangeJuice) { continue; }

                        // 14. The Japanese person plays chess.
                        idx_t japanese = 0U, chess = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(nationalities[i] == Nationality::Japanese) { japanese = i; }
                            if(hobbies[i] == Hobby::Chess) { chess = i; }
                        }
                        if(japanese != chess) { continue; }

                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        idx_t reading = 0U, fox = 0U;
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(hobbies[i] == Hobby::Reading) { reading = i; }
                            if(pets[i] == Pet::Fox) { fox = i; }
                        }
                        if(!IsNeighbor(reading, fox)) { continue; }

                        // All constraints satisfied, build solution
                        Solution sol{};
                        for(idx_t i = 0U; i < kNumHouses; ++i) {
                            if(drinks[i] == Drink::Water) {
                                sol.drinksWater = ToString(nationalities[i]);
                            }
                            if(pets[i] == Pet::Zebra) {
                                sol.ownsZebra = ToString(nationalities[i]);
                            }
                        }
                        return sol;
                    } while(std::next_permutation(hobbies.begin(), hobbies.end()));
                } while(std::next_permutation(drinks.begin(), drinks.end()));
            } while(std::next_permutation(pets.begin(), pets.end()));
        } while(std::next_permutation(nationalities.begin(), nationalities.end()));
    } while(std::next_permutation(colors.begin(), colors.end()));

    // If no solution found, return empty
    return Solution{};
}

}  // namespace zebra_puzzle
