#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

using namespace std;

// Define all possible values
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Helper function to convert enum to string
string nationalityToString(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
    }
    return "";
}

string petToString(Pet p) {
    switch (p) {
        case Pet::Dog: return "dog";
        case Pet::Snails: return "snails";
        case Pet::Fox: return "fox";
        case Pet::Horse: return "horse";
        case Pet::Zebra: return "zebra";
    }
    return "";
}

struct House {
    Nationality nationality;
    Color color;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

bool satisfiesConstraints(const array<House, 5>& houses) {
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].nationality == Nationality::Englishman) && (houses[i].color != Color::Red)) {
            return false;
        }
    }
    
    // 3. The Spaniard owns the dog.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].nationality == Nationality::Spaniard) && (houses[i].pet != Pet::Dog)) {
            return false;
        }
    }
    
    // 4. The person in the green house drinks coffee.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].color == Color::Green) && (houses[i].drink != Drink::Coffee)) {
            return false;
        }
    }
    
    // 5. The Ukrainian drinks tea.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].nationality == Nationality::Ukrainian) && (houses[i].drink != Drink::Tea)) {
            return false;
        }
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (std::int32_t i = 1; i < 5; i++) {
        if ((houses[i].color == Color::Green) && (houses[i-1].color == Color::Ivory)) {
            found = true;
            break;
        }
    }
    if (!found) { return false; }
    
    // 7. The snail owner likes to go dancing.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].pet == Pet::Snails) && (houses[i].hobby != Hobby::Dancing)) {
            return false;
        }
    }
    
    // 8. The person in the yellow house is a painter.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].color == Color::Yellow) && (houses[i].hobby != Hobby::Painting)) {
            return false;
        }
    }
    
    // 9. The person in the middle house drinks milk.
    if (houses[2].drink != Drink::Milk) { return false; }
    
    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != Nationality::Norwegian) { return false; }
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    found = false;
    for (std::int32_t i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            if (((i > 0) && (houses[i-1].pet == Pet::Fox)) || ((i < 4) && (houses[i+1].pet == Pet::Fox))) {
                found = true;
                break;
            }
        }
    }
    if (!found) { return false; }
    
    // 12. The painter's house is next to the house with the horse.
    found = false;
    for (std::int32_t i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            if (((i > 0) && (houses[i-1].pet == Pet::Horse)) || ((i < 4) && (houses[i+1].pet == Pet::Horse))) {
                found = true;
                break;
            }
        }
    }
    if (!found) { return false; }
    
    // 13. The person who plays football drinks orange juice.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].hobby == Hobby::Football) && (houses[i].drink != Drink::OrangeJuice)) {
            return false;
        }
    }
    
    // 14. The Japanese person plays chess.
    for (std::int32_t i = 0; i < 5; i++) {
        if ((houses[i].nationality == Nationality::Japanese) && (houses[i].hobby != Hobby::Chess)) {
            return false;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    bool next_to_blue = false;
    if ((0 > 0) && (houses[0-1].color == Color::Blue)) { next_to_blue = true; }
    if ((0 < 4) && (houses[0+1].color == Color::Blue)) { next_to_blue = true; }
    if (!next_to_blue) { return false; }
    
    return true;
}

Solution solve() {
    array<House, 5> houses;
    
    // Generate all permutations for each category
    array<Nationality, 5> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Color, 5> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Drink, 5> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    array<Pet, 5> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Hobby, 5> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    do {
        // Set nationalities
        for (std::int32_t i = 0; i < 5; i++) {
            houses[i].nationality = nationalities[i];
        }
        // Check if Norwegian is in first house
        if (houses[0].nationality != Nationality::Norwegian) { continue; }
        
        do {
            for (std::int32_t i = 0; i < 5; i++) {
                houses[i].color = colors[i];
            }
            // Check constraint 15: Norwegian next to blue house
            bool next_to_blue = false;
            for (std::int32_t i = 0; i < 5; i++) {
                if (houses[i].nationality == Nationality::Norwegian) {
                    if ((i > 0) && (houses[i-1].color == Color::Blue)) { next_to_blue = true; }
                    if ((i < 4) && (houses[i+1].color == Color::Blue)) { next_to_blue = true; }
                    break;
                }
            }
            if (!next_to_blue) { continue; }
            
            do {
                for (std::int32_t i = 0; i < 5; i++) {
                    houses[i].drink = drinks[i];
                }
                // Check middle house drinks milk
                if (houses[2].drink != Drink::Milk) { continue; }
                
                do {
                    for (std::int32_t i = 0; i < 5; i++) {
                        houses[i].pet = pets[i];
                    }
                    do {
                        for (std::int32_t i = 0; i < 5; i++) {
                            houses[i].hobby = hobbies[i];
                        }
                        if (satisfiesConstraints(houses)) {
                            // Find answers
                            Solution solution;
                            for (const auto& house : houses) {
                                if (house.drink == Drink::Water) {
                                    solution.drinksWater = nationalityToString(house.nationality);
                                }
                                if (house.pet == Pet::Zebra) {
                                    solution.ownsZebra = nationalityToString(house.nationality);
                                }
                            }
                            return solution;
                        }
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(colors.begin(), colors.end()));
    } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    
    return Solution();
}

}  // namespace zebra_puzzle
