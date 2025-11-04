#include "zebra_puzzle.h"
#include <cstdint>
#include <array>
#include <algorithm>

namespace zebra_puzzle {

// Define enums for all attributes
enum Color : std::uint8_t {
    RED = 0,
    GREEN = 1,
    IVORY = 2,
    YELLOW = 3,
    BLUE = 4
};

enum Nationality : std::uint8_t {
    ENGLISHMAN = 0,
    SPANIARD = 1,
    UKRAINIAN = 2,
    NORWEGIAN = 3,
    JAPANESE = 4
};

enum Pet : std::uint8_t {
    DOG = 0,
    SNAIL = 1,
    FOX = 2,
    HORSE = 3,
    ZEBRA = 4
};

enum Drink : std::uint8_t {
    COFFEE = 0,
    TEA = 1,
    MILK = 2,
    ORANGE_JUICE = 3,
    WATER = 4
};

enum Hobby : std::uint8_t {
    DANCING = 0,
    PAINTING = 1,
    READING = 2,
    FOOTBALL = 3,
    CHESS = 4
};

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

using Houses = std::array<House, 5>;

// Helper function to check if all values in an attribute are unique
template<typename T>
bool allUnique(const Houses& houses, T House::*member) {
    std::array<bool, 5> used = {false, false, false, false, false};
    for (std::uint8_t i = 0; i < 5; ++i) {
        std::uint8_t value = static_cast<std::uint8_t>(houses[i].*member);
        if (used[value]) {
            return false;
        }
        used[value] = true;
    }
    return true;
}

// Check if the current configuration satisfies all constraints
bool checkConstraints(const Houses& houses) {
    // Check uniqueness constraints
    if (!allUnique(houses, &House::color)) {
        return false;
    }
    if (!allUnique(houses, &House::nationality)) {
        return false;
    }
    if (!allUnique(houses, &House::pet)) {
        return false;
    }
    if (!allUnique(houses, &House::drink)) {
        return false;
    }
    if (!allUnique(houses, &House::hobby)) {
        return false;
    }
    
    // Constraint 2: The Englishman lives in the red house
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == ENGLISHMAN) {
            if (houses[i].color != RED) {
                return false;
            }
        }
    }
    
    // Constraint 3: The Spaniard owns the dog
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == SPANIARD) {
            if (houses[i].pet != DOG) {
                return false;
            }
        }
    }
    
    // Constraint 4: The person in the green house drinks coffee
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].color == GREEN) {
            if (houses[i].drink != COFFEE) {
                return false;
            }
        }
    }
    
    // Constraint 5: The Ukrainian drinks tea
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == UKRAINIAN) {
            if (houses[i].drink != TEA) {
                return false;
            }
        }
    }
    
    // Constraint 6: The green house is immediately to the right of the ivory house
    bool found_ivory_green = false;
    for (std::uint8_t i = 0; i < 4; ++i) {
        if ((houses[i].color == IVORY) && (houses[i + 1].color == GREEN)) {
            found_ivory_green = true;
            break;
        }
    }
    if (!found_ivory_green) {
        return false;
    }
    
    // Constraint 7: The snail owner likes to go dancing
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].pet == SNAIL) {
            if (houses[i].hobby != DANCING) {
                return false;
            }
        }
    }
    
    // Constraint 8: The person in the yellow house is a painter
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].color == YELLOW) {
            if (houses[i].hobby != PAINTING) {
                return false;
            }
        }
    }
    
    // Constraint 9: The person in the middle house drinks milk
    if (houses[2].drink != MILK) {
        return false;
    }
    
    // Constraint 10: The Norwegian lives in the first house
    if (houses[0].nationality != NORWEGIAN) {
        return false;
    }
    
    // Constraint 11: The person who enjoys reading lives next to the person with the fox
    bool reading_next_to_fox = false;
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].hobby == READING) {
            if (i > 0) {
                if (houses[i - 1].pet == FOX) {
                    reading_next_to_fox = true;
                    break;
                }
            }
            if (i < 4) {
                if (houses[i + 1].pet == FOX) {
                    reading_next_to_fox = true;
                    break;
                }
            }
        }
    }
    if (!reading_next_to_fox) {
        return false;
    }
    
    // Constraint 12: The painter's house is next to the house with the horse
    bool painter_next_to_horse = false;
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].hobby == PAINTING) {
            if (i > 0) {
                if (houses[i - 1].pet == HORSE) {
                    painter_next_to_horse = true;
                    break;
                }
            }
            if (i < 4) {
                if (houses[i + 1].pet == HORSE) {
                    painter_next_to_horse = true;
                    break;
                }
            }
        }
    }
    if (!painter_next_to_horse) {
        return false;
    }
    
    // Constraint 13: The person who plays football drinks orange juice
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].hobby == FOOTBALL) {
            if (houses[i].drink != ORANGE_JUICE) {
                return false;
            }
        }
    }
    
    // Constraint 14: The Japanese person plays chess
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == JAPANESE) {
            if (houses[i].hobby != CHESS) {
                return false;
            }
        }
    }
    
    // Constraint 15: The Norwegian lives next to the blue house
    bool norwegian_next_to_blue = false;
    for (std::uint8_t i = 0; i < 5; ++i) {
        if (houses[i].nationality == NORWEGIAN) {
            if (i > 0) {
                if (houses[i - 1].color == BLUE) {
                    norwegian_next_to_blue = true;
                    break;
                }
            }
            if (i < 4) {
                if (houses[i + 1].color == BLUE) {
                    norwegian_next_to_blue = true;
                    break;
                }
            }
        }
    }
    if (!norwegian_next_to_blue) {
        return false;
    }
    
    return true;
}

Solution solve() {
    // Initialize houses with constraint 9 and 10 already applied
    Houses houses;
    houses[0].nationality = NORWEGIAN;  // Constraint 10
    houses[2].drink = MILK;  // Constraint 9
    
    // Generate all permutations for colors
    std::array<Color, 5> colors = {RED, GREEN, IVORY, YELLOW, BLUE};
    
    do {
        // Check constraint 6 early: green must be immediately right of ivory
        bool valid_color = false;
        for (std::uint8_t i = 0; i < 4; ++i) {
            if ((colors[i] == IVORY) && (colors[i + 1] == GREEN)) {
                valid_color = true;
                break;
            }
        }
        if (!valid_color) {
            continue;
        }
        
        // Check constraint 15 early: Norwegian (house 0) must be next to blue
        if ((colors[1] != BLUE)) {
            continue;
        }
        
        for (std::uint8_t i = 0; i < 5; ++i) {
            houses[i].color = colors[i];
        }
        
        // Generate all permutations for nationalities (except Norwegian which is fixed)
        std::array<Nationality, 4> other_nationalities = {ENGLISHMAN, SPANIARD, UKRAINIAN, JAPANESE};
        
        do {
            houses[1].nationality = other_nationalities[0];
            houses[2].nationality = other_nationalities[1];
            houses[3].nationality = other_nationalities[2];
            houses[4].nationality = other_nationalities[3];
            
            // Generate all permutations for pets
            std::array<Pet, 5> pets = {DOG, SNAIL, FOX, HORSE, ZEBRA};
            
            do {
                for (std::uint8_t i = 0; i < 5; ++i) {
                    houses[i].pet = pets[i];
                }
                
                // Generate all permutations for drinks (except milk which is fixed)
                std::array<Drink, 4> other_drinks = {COFFEE, TEA, ORANGE_JUICE, WATER};
                
                do {
                    houses[0].drink = other_drinks[0];
                    houses[1].drink = other_drinks[1];
                    houses[3].drink = other_drinks[2];
                    houses[4].drink = other_drinks[3];
                    
                    // Generate all permutations for hobbies
                    std::array<Hobby, 5> hobbies = {DANCING, PAINTING, READING, FOOTBALL, CHESS};
                    
                    do {
                        for (std::uint8_t i = 0; i < 5; ++i) {
                            houses[i].hobby = hobbies[i];
                        }
                        
                        // Check all constraints
                        if (checkConstraints(houses)) {
                            // Found the solution!
                            Solution solution;
                            
                            // Find who drinks water
                            for (std::uint8_t i = 0; i < 5; ++i) {
                                if (houses[i].drink == WATER) {
                                    switch (houses[i].nationality) {
                                        case ENGLISHMAN:
                                            solution.drinksWater_ = "Englishman";
                                            break;
                                        case SPANIARD:
                                            solution.drinksWater_ = "Spaniard";
                                            break;
                                        case UKRAINIAN:
                                            solution.drinksWater_ = "Ukrainian";
                                            break;
                                        case NORWEGIAN:
                                            solution.drinksWater_ = "Norwegian";
                                            break;
                                        case JAPANESE:
                                            solution.drinksWater_ = "Japanese";
                                            break;
                                    }
                                    break;
                                }
                            }
                            
                            // Find who owns the zebra
                            for (std::uint8_t i = 0; i < 5; ++i) {
                                if (houses[i].pet == ZEBRA) {
                                    switch (houses[i].nationality) {
                                        case ENGLISHMAN:
                                            solution.ownsZebra_ = "Englishman";
                                            break;
                                        case SPANIARD:
                                            solution.ownsZebra_ = "Spaniard";
                                            break;
                                        case UKRAINIAN:
                                            solution.ownsZebra_ = "Ukrainian";
                                            break;
                                        case NORWEGIAN:
                                            solution.ownsZebra_ = "Norwegian";
                                            break;
                                        case JAPANESE:
                                            solution.ownsZebra_ = "Japanese";
                                            break;
                                    }
                                    break;
                                }
                            }
                            
                            return solution;
                        }
                        
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                    
                } while (std::next_permutation(other_drinks.begin(), other_drinks.end()));
                
            } while (std::next_permutation(pets.begin(), pets.end()));
            
        } while (std::next_permutation(other_nationalities.begin(), other_nationalities.end()));
        
    } while (std::next_permutation(colors.begin(), colors.end()));
    
    // Should never reach here if the puzzle has a solution
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
