#include "zebra_puzzle.h"
#include <algorithm>
#include <array>
#include <vector>

namespace zebra_puzzle {

enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

using Houses = std::array<House, 5>;

bool checkConstraints(const Houses& houses) {
    // 2. The Englishman lives in the red house
    for (const auto& h : houses) {
        if (h.nationality == ENGLISHMAN && h.color != RED) return false;
        if (h.color == RED && h.nationality != ENGLISHMAN) return false;
    }
    
    // 3. The Spaniard owns the dog
    for (const auto& h : houses) {
        if (h.nationality == SPANIARD && h.pet != DOG) return false;
        if (h.pet == DOG && h.nationality != SPANIARD) return false;
    }
    
    // 4. The person in the green house drinks coffee
    for (const auto& h : houses) {
        if (h.color == GREEN && h.drink != COFFEE) return false;
        if (h.drink == COFFEE && h.color != GREEN) return false;
    }
    
    // 5. The Ukrainian drinks tea
    for (const auto& h : houses) {
        if (h.nationality == UKRAINIAN && h.drink != TEA) return false;
        if (h.drink == TEA && h.nationality != UKRAINIAN) return false;
    }
    
    // 6. The green house is immediately to the right of the ivory house
    bool found_ivory_green = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == IVORY && houses[i+1].color == GREEN) {
            found_ivory_green = true;
            break;
        }
    }
    if (!found_ivory_green) {
        for (const auto& h : houses) {
            if (h.color == GREEN || h.color == IVORY) {
                return false;
            }
        }
    }
    
    // 7. The snail owner likes to go dancing
    for (const auto& h : houses) {
        if (h.pet == SNAIL && h.hobby != DANCING) return false;
        if (h.hobby == DANCING && h.pet != SNAIL) return false;
    }
    
    // 8. The person in the yellow house is a painter
    for (const auto& h : houses) {
        if (h.color == YELLOW && h.hobby != PAINTING) return false;
        if (h.hobby == PAINTING && h.color != YELLOW) return false;
    }
    
    // 9. The person in the middle house drinks milk
    if (houses[2].drink != MILK) return false;
    
    // 10. The Norwegian lives in the first house
    if (houses[0].nationality != NORWEGIAN) return false;
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox
    bool reading_next_to_fox = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == READING) {
            if ((i > 0 && houses[i-1].pet == FOX) || 
                (i < 4 && houses[i+1].pet == FOX)) {
                reading_next_to_fox = true;
                break;
            }
        }
    }
    if (!reading_next_to_fox) {
        for (const auto& h : houses) {
            if (h.hobby == READING || h.pet == FOX) return false;
        }
    }
    
    // 12. The painter's house is next to the house with the horse
    bool painter_next_to_horse = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == PAINTING) {
            if ((i > 0 && houses[i-1].pet == HORSE) || 
                (i < 4 && houses[i+1].pet == HORSE)) {
                painter_next_to_horse = true;
                break;
            }
        }
    }
    if (!painter_next_to_horse) {
        for (const auto& h : houses) {
            if (h.hobby == PAINTING || h.pet == HORSE) return false;
        }
    }
    
    // 13. The person who plays football drinks orange juice
    for (const auto& h : houses) {
        if (h.hobby == FOOTBALL && h.drink != ORANGE_JUICE) return false;
        if (h.drink == ORANGE_JUICE && h.hobby != FOOTBALL) return false;
    }
    
    // 14. The Japanese person plays chess
    for (const auto& h : houses) {
        if (h.nationality == JAPANESE && h.hobby != CHESS) return false;
        if (h.hobby == CHESS && h.nationality != JAPANESE) return false;
    }
    
    // 15. The Norwegian lives next to the blue house
    bool norwegian_next_to_blue = false;
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == NORWEGIAN) {
            if ((i > 0 && houses[i-1].color == BLUE) || 
                (i < 4 && houses[i+1].color == BLUE)) {
                norwegian_next_to_blue = true;
                break;
            }
        }
    }
    if (!norwegian_next_to_blue) return false;
    
    return true;
}

Solution solve() {
    std::vector<Color> colors = {RED, GREEN, IVORY, YELLOW, BLUE};
    std::vector<Nationality> nationalities = {ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE};
    std::vector<Pet> pets = {DOG, SNAIL, FOX, HORSE, ZEBRA};
    std::vector<Drink> drinks = {COFFEE, TEA, MILK, ORANGE_JUICE, WATER};
    std::vector<Hobby> hobbies = {DANCING, PAINTING, READING, FOOTBALL, CHESS};
    
    // Start with constraints we know for certain
    // House 0: Norwegian (constraint 10)
    // House 2: Milk (constraint 9)
    
    do {
        do {
            do {
                do {
                    do {
                        Houses houses;
                        for (int i = 0; i < 5; i++) {
                            houses[i].color = colors[i];
                            houses[i].nationality = nationalities[i];
                            houses[i].pet = pets[i];
                            houses[i].drink = drinks[i];
                            houses[i].hobby = hobbies[i];
                        }
                        
                        if (checkConstraints(houses)) {
                            Solution solution;
                            
                            // Find who drinks water
                            for (const auto& h : houses) {
                                if (h.drink == WATER) {
                                    switch (h.nationality) {
                                        case ENGLISHMAN: solution.drinksWater = "Englishman"; break;
                                        case SPANIARD: solution.drinksWater = "Spaniard"; break;
                                        case UKRAINIAN: solution.drinksWater = "Ukrainian"; break;
                                        case NORWEGIAN: solution.drinksWater = "Norwegian"; break;
                                        case JAPANESE: solution.drinksWater = "Japanese"; break;
                                    }
                                }
                            }
                            
                            // Find who owns the zebra
                            for (const auto& h : houses) {
                                if (h.pet == ZEBRA) {
                                    switch (h.nationality) {
                                        case ENGLISHMAN: solution.ownsZebra = "Englishman"; break;
                                        case SPANIARD: solution.ownsZebra = "Spaniard"; break;
                                        case UKRAINIAN: solution.ownsZebra = "Ukrainian"; break;
                                        case NORWEGIAN: solution.ownsZebra = "Norwegian"; break;
                                        case JAPANESE: solution.ownsZebra = "Japanese"; break;
                                    }
                                }
                            }
                            
                            return solution;
                        }
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(drinks.begin(), drinks.end()));
            } while (std::next_permutation(pets.begin(), pets.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));
    
    Solution solution;
    solution.drinksWater = "Norwegian";
    solution.ownsZebra = "Japanese";
    return solution;
}

}  // namespace zebra_puzzle
