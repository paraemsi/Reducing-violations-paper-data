#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

// Define the categories
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Reading, Painting, Football, Chess };

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

// The solve function
Solution solve() {
    // Prepare the values
    array<Color, 5> allColors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Nationality, 5> allNationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                              Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Pet, 5> allPets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Drink, 5> allDrinks = {Drink::Coffee, Drink::Tea, Drink::Milk, 
                                 Drink::OrangeJuice, Drink::Water};
    array<Hobby, 5> allHobbies = {Hobby::Dancing, Hobby::Reading, Hobby::Painting, 
                                  Hobby::Football, Hobby::Chess};
    
    Solution solution;
    
    // Generate all permutations and check constraints
    // Start with nationalities to fix Norwegian in first position
    array<Nationality, 5> nationalities = allNationalities;
    do {
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        array<Color, 5> colors = allColors;
        do {
            // Constraint 15: Norwegian lives next to blue house
            bool norwegianNextToBlue = false;
            for (int i = 0; i < 5; i++) {
                if (nationalities[i] == Nationality::Norwegian) {
                    if ((i > 0 && colors[i - 1] == Color::Blue) || 
                        (i < 4 && colors[i + 1] == Color::Blue)) {
                        norwegianNextToBlue = true;
                        break;
                    }
                }
            }
            if (!norwegianNextToBlue) continue;
            
            // Constraint 2: Englishman in red house
            bool englishmanInRed = true;
            for (int i = 0; i < 5; i++) {
                if (nationalities[i] == Nationality::Englishman && colors[i] != Color::Red) {
                    englishmanInRed = false;
                    break;
                }
            }
            if (!englishmanInRed) continue;
            
            // Constraint 6: Green is immediately right of ivory
            bool greenRightOfIvory = false;
            for (int i = 0; i < 4; i++) {
                if (colors[i] == Color::Ivory && colors[i + 1] == Color::Green) {
                    greenRightOfIvory = true;
                    break;
                }
            }
            if (!greenRightOfIvory) continue;
            
            array<Drink, 5> drinks = allDrinks;
            do {
                // Constraint 9: Middle house drinks milk
                if (drinks[2] != Drink::Milk) continue;
                
                // Constraint 4: Green house drinks coffee
                bool greenDrinksCoffee = true;
                for (int i = 0; i < 5; i++) {
                    if (colors[i] == Color::Green && drinks[i] != Drink::Coffee) {
                        greenDrinksCoffee = false;
                        break;
                    }
                }
                if (!greenDrinksCoffee) continue;
                
                // Constraint 5: Ukrainian drinks tea
                bool ukrainianDrinksTea = true;
                for (int i = 0; i < 5; i++) {
                    if (nationalities[i] == Nationality::Ukrainian && drinks[i] != Drink::Tea) {
                        ukrainianDrinksTea = false;
                        break;
                    }
                }
                if (!ukrainianDrinksTea) continue;
                
                array<Pet, 5> pets = allPets;
                do {
                    // Constraint 3: Spaniard owns dog
                    bool spaniardOwnsDog = true;
                    for (int i = 0; i < 5; i++) {
                        if (nationalities[i] == Nationality::Spaniard && pets[i] != Pet::Dog) {
                            spaniardOwnsDog = false;
                            break;
                        }
                    }
                    if (!spaniardOwnsDog) continue;
                    
                    array<Hobby, 5> hobbies = allHobbies;
                    do {
                        // Constraint 7: Snail owner likes dancing
                        bool snailOwnerDances = true;
                        for (int i = 0; i < 5; i++) {
                            if (pets[i] == Pet::Snails && hobbies[i] != Hobby::Dancing) {
                                snailOwnerDances = false;
                                break;
                            }
                        }
                        if (!snailOwnerDances) continue;
                        
                        // Constraint 8: Yellow house is painter
                        bool yellowHousePainter = true;
                        for (int i = 0; i < 5; i++) {
                            if (colors[i] == Color::Yellow && hobbies[i] != Hobby::Painting) {
                                yellowHousePainter = false;
                                break;
                            }
                        }
                        if (!yellowHousePainter) continue;
                        
                        // Constraint 13: Football player drinks orange juice
                        bool footballDrinksOJ = true;
                        for (int i = 0; i < 5; i++) {
                            if (hobbies[i] == Hobby::Football && drinks[i] != Drink::OrangeJuice) {
                                footballDrinksOJ = false;
                                break;
                            }
                        }
                        if (!footballDrinksOJ) continue;
                        
                        // Constraint 14: Japanese plays chess
                        bool japanesePlaysChess = true;
                        for (int i = 0; i < 5; i++) {
                            if (nationalities[i] == Nationality::Japanese && hobbies[i] != Hobby::Chess) {
                                japanesePlaysChess = false;
                                break;
                            }
                        }
                        if (!japanesePlaysChess) continue;
                        
                        // Constraint 11: Reader next to fox owner
                        bool readerNextToFox = false;
                        for (int i = 0; i < 5; i++) {
                            if (hobbies[i] == Hobby::Reading) {
                                if ((i > 0 && pets[i - 1] == Pet::Fox) || 
                                    (i < 4 && pets[i + 1] == Pet::Fox)) {
                                    readerNextToFox = true;
                                    break;
                                }
                            }
                        }
                        if (!readerNextToFox) continue;
                        
                        // Constraint 12: Painter next to horse owner
                        bool painterNextToHorse = false;
                        for (int i = 0; i < 5; i++) {
                            if (hobbies[i] == Hobby::Painting) {
                                if ((i > 0 && pets[i - 1] == Pet::Horse) || 
                                    (i < 4 && pets[i + 1] == Pet::Horse)) {
                                    painterNextToHorse = true;
                                    break;
                                }
                            }
                        }
                        if (!painterNextToHorse) continue;
                        
                        // Found valid solution
                        for (int i = 0; i < 5; i++) {
                            if (drinks[i] == Drink::Water) {
                                solution.drinksWater = nationalityToString(nationalities[i]);
                            }
                            if (pets[i] == Pet::Zebra) {
                                solution.ownsZebra = nationalityToString(nationalities[i]);
                            }
                        }
                        return solution;
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(drinks.begin(), drinks.end()));
        } while (next_permutation(colors.begin(), colors.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return solution;
}

}  // namespace zebra_puzzle
