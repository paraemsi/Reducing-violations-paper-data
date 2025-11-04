#include "zebra_puzzle.h"
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <cstdint>

namespace zebra_puzzle {

// Define the categories
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Helper function to convert to string
std::string nationalityToString(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
    }
    return "";
}

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

bool checkConstraints(const std::array<House, 5>& houses) {
    // Check all constraints
    for (std::int32_t i = 0; i < 5; i++) {
        const auto& h = houses[i];
        // 2. The Englishman lives in the red house.
        if ((h.nationality == Nationality::Englishman) && (h.color != Color::Red)) return false;
        // 3. The Spaniard owns the dog.
        if ((h.nationality == Nationality::Spaniard) && (h.pet != Pet::Dog)) return false;
        // 4. The person in the green house drinks coffee.
        if ((h.color == Color::Green) && (h.drink != Drink::Coffee)) return false;
        // 5. The Ukrainian drinks tea.
        if ((h.nationality == Nationality::Ukrainian) && (h.drink != Drink::Tea)) return false;
        // 7. The snail owner likes to go dancing.
        if ((h.pet == Pet::Snails) && (h.hobby != Hobby::Dancing)) return false;
        // 8. The person in the yellow house is a painter.
        if ((h.color == Color::Yellow) && (h.hobby != Hobby::Painting)) return false;
        // 13. The person who plays football drinks orange juice.
        if ((h.hobby == Hobby::Football) && (h.drink != Drink::OrangeJuice)) return false;
        // 14. The Japanese person plays chess.
        if ((h.nationality == Nationality::Japanese) && (h.hobby != Hobby::Chess)) return false;
    }
    
    // Check constraints that involve multiple houses
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (std::int32_t i = 0; i < 4; i++) {
        if ((houses[i].color == Color::Ivory) && (houses[i + 1].color == Color::Green)) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 9. The person in the middle house drinks milk.
    if (houses[2].drink != Drink::Milk) return false;
    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != Nationality::Norwegian) return false;
    
    // 11. The person who enjoys reading lives next to the person with the fox.
    // 12. The painter's house is next to the house with the horse.
    // 15. The Norwegian lives next to the blue house.
    bool readingNextToFox = false;
    bool paintingNextToHorse = false;
    bool norwegianNextToBlue = false;
    for (std::int32_t i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            if ((i > 0) && (houses[i-1].pet == Pet::Fox)) readingNextToFox = true;
            if ((i < 4) && (houses[i+1].pet == Pet::Fox)) readingNextToFox = true;
        }
        if (houses[i].hobby == Hobby::Painting) {
            if ((i > 0) && (houses[i-1].pet == Pet::Horse)) paintingNextToHorse = true;
            if ((i < 4) && (houses[i+1].pet == Pet::Horse)) paintingNextToHorse = true;
        }
        if (houses[i].nationality == Nationality::Norwegian) {
            if ((i > 0) && (houses[i-1].color == Color::Blue)) norwegianNextToBlue = true;
            if ((i < 4) && (houses[i+1].color == Color::Blue)) norwegianNextToBlue = true;
        }
    }
    if (!(readingNextToFox && paintingNextToHorse && norwegianNextToBlue)) return false;
    
    return true;
}

Solution solve() {
    // Generate all possible permutations and check constraints
    std::array<House, 5> houses;
    
    // Colors
    std::vector<Color> colors{Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    do {
        // Fix blue in second position (index 1) because Norwegian is next to blue and in first house
        if (colors[1] != Color::Blue) continue;
        for (std::int32_t i = 0; i < 5; i++) houses[i].color = colors[i];
        
        // Nationalities
        std::vector<Nationality> nationalities{Nationality::Englishman, Nationality::Spaniard, 
                                          Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
        do {
            // Fix Norwegian in first position
            if (nationalities[0] != Nationality::Norwegian) continue;
            for (std::int32_t i = 0; i < 5; i++) houses[i].nationality = nationalities[i];
            
            // Drinks
            std::vector<Drink> drinks{Drink::Coffee, Drink::Tea, Drink::Milk, 
                                 Drink::OrangeJuice, Drink::Water};
            do {
                // Fix milk in third position (index 2)
                if (drinks[2] != Drink::Milk) continue;
                for (std::int32_t i = 0; i < 5; i++) houses[i].drink = drinks[i];
                
                // Pets and Hobbies
                std::vector<Pet> pets{Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
                do {
                    for (std::int32_t i = 0; i < 5; i++) houses[i].pet = pets[i];
                    
                    std::vector<Hobby> hobbies{Hobby::Dancing, Hobby::Painting, Hobby::Reading, 
                                          Hobby::Football, Hobby::Chess};
                    do {
                        for (std::int32_t i = 0; i < 5; i++) houses[i].hobby = hobbies[i];
                        
                        if (checkConstraints(houses)) {
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
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));
    
    return Solution{};
}

}  // namespace zebra_puzzle
