#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>

namespace zebra_puzzle {

using namespace std;

// Define the categories
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct House {
    Nationality nationality;
    Color color;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

bool satisfies_constraints(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // 2. The Englishman lives in the red house.
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. The Spaniard owns the dog.
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. The person in the green house drinks coffee.
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. The Ukrainian drinks tea.
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 7. The snail owner likes to go dancing.
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. The person in the yellow house is a painter.
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && h.drink != Drink::Milk) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && h.nationality != Nationality::Norwegian) return false;
        // 13. The person who plays football drinks orange juice.
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. The Japanese person plays chess.
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    }
    
    // Check neighbor constraints
    for (int i = 0; i < 5; i++) {
        // 6. The green house is immediately to the right of the ivory house.
        if (houses[i].color == Color::Ivory) {
            if (i == 4 || houses[i + 1].color != Color::Green) return false;
        }
        // 11. The person who enjoys reading lives in the house next to the person with the fox.
        if (houses[i].hobby == Hobby::Reading) {
            bool found = false;
            if (i > 0 && houses[i - 1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Fox) found = true;
            if (!found) return false;
        }
        // 12. The painter's house is next to the house with the horse.
        if (houses[i].hobby == Hobby::Painting) {
            bool found = false;
            if (i > 0 && houses[i - 1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Horse) found = true;
            if (!found) return false;
        }
        // 15. The Norwegian lives next to the blue house.
        if (houses[i].nationality == Nationality::Norwegian) {
            bool found = false;
            if (i > 0 && houses[i - 1].color == Color::Blue) found = true;
            if (i < 4 && houses[i + 1].color == Color::Blue) found = true;
            if (!found) return false;
        }
    }
    return true;
}

Solution solve() {
    array<House, 5> houses;
    
    // Generate all possible permutations, fixing known values
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                         Nationality::Ukrainian, Nationality::Norwegian, 
                                         Nationality::Japanese};
    // Fix Norwegian to be first
    // We'll generate permutations where index 0 is always Norwegian
    // So swap Norwegian to the first position
    iter_swap(find(nationalities.begin(), nationalities.end(), Nationality::Norwegian), nationalities.begin());
    // Now generate permutations of the remaining elements
    
    // Similarly for drinks, fix milk to be in the middle
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, 
                            Drink::OrangeJuice, Drink::Water};
    iter_swap(find(drinks.begin(), drinks.end(), Drink::Milk), drinks.begin() + 2);
    
    // Generate all permutations and check
    do {
        // Skip if first nationality is not Norwegian (but it should always be due to our swap)
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
        do {
            // Check if green is immediately to the right of ivory
            bool green_right_of_ivory = false;
            for (int i = 0; i < 4; i++) {
                if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                    green_right_of_ivory = true;
                    break;
                }
            }
            if (!green_right_of_ivory) continue;
            
            do {
                // Check if milk is in the middle
                if (drinks[2] != Drink::Milk) continue;
                
                vector<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
                do {
                    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, 
                                             Hobby::Football, Hobby::Chess};
                    do {
                        // Assign to houses
                        for (int i = 0; i < 5; i++) {
                            houses[i] = {nationalities[i], colors[i], drinks[i], pets[i], hobbies[i]};
                        }
                        if (satisfies_constraints(houses)) {
                            Solution solution;
                            for (const auto& house : houses) {
                                if (house.drink == Drink::Water) {
                                    switch (house.nationality) {
                                        case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                        case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                        case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                        case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                        case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                    }
                                }
                                if (house.pet == Pet::Zebra) {
                                    switch (house.nationality) {
                                        case Nationality::Englishman: solution.ownsZebra = "Englishman"; break;
                                        case Nationality::Spaniard: solution.ownsZebra = "Spaniard"; break;
                                        case Nationality::Ukrainian: solution.ownsZebra = "Ukrainian"; break;
                                        case Nationality::Norwegian: solution.ownsZebra = "Norwegian"; break;
                                        case Nationality::Japanese: solution.ownsZebra = "Japanese"; break;
                                    }
                                }
                            }
                            return solution;
                        }
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin() + 3, drinks.end())); // Permute remaining elements
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin() + 1, nationalities.end())); // Permute remaining nationalities
    
    return Solution{};
}

}  // namespace zebra_puzzle
