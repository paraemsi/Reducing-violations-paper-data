#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

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
    // 2. The Englishman lives in the red house.
    for (int32_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Englishman && 
            houses[i].color != Color::Red) {
            return false;
        }
    }
    // 3. The Spaniard owns the dog.
    for (int32_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Spaniard && 
            houses[i].pet != Pet::Dog) {
            return false;
        }
    }
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].color == Color::Green && 
            houses[i].drink != Drink::Coffee) {
            return false;
        }
    }
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Ukrainian && 
            houses[i].drink != Drink::Tea) {
            return false;
        }
    }
    // 6. The green house is immediately to the right of the ivory house.
    // Fixed by our initial setup, so always true
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].pet == Pet::Snails && 
            houses[i].hobby != Hobby::Dancing) {
            return false;
        }
    }
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].color == Color::Yellow && 
            houses[i].hobby != Hobby::Painting) {
            return false;
        }
    }
    // 9. The person in the middle house drinks milk. (Fixed)
    // 10. The Norwegian lives in the first house. (Fixed)
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Reading) {
            bool found = false;
            if (i > 0 && houses[i-1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Fox) found = true;
            if (!found) return false;
        }
    }
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Painting) {
            bool found = false;
            if (i > 0 && houses[i-1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i+1].pet == Pet::Horse) found = true;
            if (!found) return false;
        }
    }
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].hobby == Hobby::Football && 
            houses[i].drink != Drink::OrangeJuice) {
            return false;
        }
    }
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; ++i) {
        if (houses[i].nationality == Nationality::Japanese && 
            houses[i].hobby != Hobby::Chess) {
            return false;
        }
    }
    // 15. The Norwegian lives next to the blue house. (Fixed by initial setup)
    return true;
}

Solution solve() {
    // Fixed values
    array<House, 5> houses;
    // Set fixed properties
    houses[0].nationality = Nationality::Norwegian;
    houses[1].color = Color::Blue;
    houses[2].drink = Drink::Milk;
    houses[3].color = Color::Ivory;
    houses[4].color = Color::Green;
    
    // Prepare all possible values and sort them
    vector<Nationality> nationalities{Nationality::Englishman, Nationality::Spaniard, 
                                      Nationality::Ukrainian, Nationality::Japanese};
    sort(nationalities.begin(), nationalities.end());
    
    vector<Color> colors{Color::Red, Color::Yellow};
    sort(colors.begin(), colors.end());
    
    vector<Drink> drinks{Drink::Coffee, Drink::Tea, Drink::OrangeJuice, Drink::Water};
    sort(drinks.begin(), drinks.end());
    
    vector<Pet> pets{Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    sort(pets.begin(), pets.end());
    
    vector<Hobby> hobbies{Hobby::Dancing, Hobby::Painting, Hobby::Reading, 
                          Hobby::Football, Hobby::Chess};
    sort(hobbies.begin(), hobbies.end());
    
    // Generate permutations and check
    do {
        // Assign nationalities (skip Norwegian which is fixed)
        houses[1].nationality = nationalities[0];
        houses[2].nationality = nationalities[1];
        houses[3].nationality = nationalities[2];
        houses[4].nationality = nationalities[3];
        
        // Assign remaining colors
        do {
            // Assign to houses without fixed colors (0,2)
            houses[0].color = colors[0];
            houses[2].color = colors[1];
            
            // Assign drinks
            do {
                // Skip house 2 which has fixed milk
                // Assign to houses 0,1,3,4
                houses[0].drink = drinks[0];
                houses[1].drink = drinks[1];
                houses[3].drink = drinks[2];
                houses[4].drink = drinks[3];
                
                // Assign pets and hobbies
                do {
                    for (int32_t i = 0; i < 5; ++i) {
                        houses[i].pet = pets[i];
                    }
                    do {
                        for (int32_t i = 0; i < 5; ++i) {
                            houses[i].hobby = hobbies[i];
                        }
                        if (satisfies_constraints(houses)) {
                            // Found valid assignment
                            Solution solution;
                            // Find who drinks water
                            for (int32_t i = 0; i < 5; ++i) {
                                if (houses[i].drink == Drink::Water) {
                                    switch (houses[i].nationality) {
                                        case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                                        case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                                        case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                                        case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                                        case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                                    }
                                }
                                if (houses[i].pet == Pet::Zebra) {
                                    switch (houses[i].nationality) {
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
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    // Should not reach here according to the puzzle
    Solution solution;
    return solution;
}

}  // namespace zebra_puzzle
