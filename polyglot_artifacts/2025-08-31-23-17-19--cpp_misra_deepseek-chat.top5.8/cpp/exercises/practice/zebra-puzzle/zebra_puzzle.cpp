#include "zebra_puzzle.h"
#include <string>
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace zebra_puzzle {

using namespace std;

// Define all possible values
constexpr int32_t num_houses = 5;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Reading, Painting, Football, Chess };

// Helper function to check if a condition is true
template<typename T>
int32_t find_index(const array<T, num_houses>& arr, T value) {
    for (int32_t i = 0; i < num_houses; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

Solution solve() {
    // Generate all permutations for each category
    array<Color, num_houses> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    array<Nationality, num_houses> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                                    Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    array<Pet, num_houses> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    array<Drink, num_houses> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    array<Hobby, num_houses> hobbies = {Hobby::Dancing, Hobby::Reading, Hobby::Painting, Hobby::Football, Hobby::Chess};
    
    Solution solution;
    
    // We need to permute all categories
    do {
        // Check if Norwegian is in first house (constraint 10)
        if (nationalities[0] != Nationality::Norwegian) continue;
        
        do {
            // Check if milk is in middle house (constraint 9)
            if (drinks[2] != Drink::Milk) continue;
            
            do {
                do {
                    do {
                        // Check all constraints
                        // 2. The Englishman lives in the red house.
                        const int32_t englishman_idx = find_index(nationalities, Nationality::Englishman);
                        const int32_t red_idx = find_index(colors, Color::Red);
                        if (englishman_idx != red_idx) continue;
                        
                        // 3. The Spaniard owns the dog.
                        const int32_t spaniard_idx = find_index(nationalities, Nationality::Spaniard);
                        const int32_t dog_idx = find_index(pets, Pet::Dog);
                        if (spaniard_idx != dog_idx) continue;
                        
                        // 4. The person in the green house drinks coffee.
                        const int32_t green_idx = find_index(colors, Color::Green);
                        if (green_idx == -1) continue;
                        if (drinks[green_idx] != Drink::Coffee) continue;
                        
                        // 5. The Ukrainian drinks tea.
                        const int32_t ukrainian_idx = find_index(nationalities, Nationality::Ukrainian);
                        if (ukrainian_idx == -1) continue;
                        if (drinks[ukrainian_idx] != Drink::Tea) continue;
                        
                        // 6. The green house is immediately to the right of the ivory house.
                        const int32_t ivory_idx = find_index(colors, Color::Ivory);
                        if (ivory_idx == -1) continue;
                        if (green_idx != ivory_idx + 1) continue;
                        
                        // 7. The snail owner likes to go dancing.
                        const int32_t snails_idx = find_index(pets, Pet::Snails);
                        if (snails_idx == -1) continue;
                        if (hobbies[snails_idx] != Hobby::Dancing) continue;
                        
                        // 8. The person in the yellow house is a painter.
                        const int32_t yellow_idx = find_index(colors, Color::Yellow);
                        if (yellow_idx == -1) continue;
                        if (hobbies[yellow_idx] != Hobby::Painting) continue;
                        
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        const int32_t reading_idx = find_index(hobbies, Hobby::Reading);
                        const int32_t fox_idx = find_index(pets, Pet::Fox);
                        if (reading_idx == -1 || fox_idx == -1) continue;
                        if ((reading_idx != fox_idx - 1) && (reading_idx != fox_idx + 1)) continue;
                        
                        // 12. The painter's house is next to the house with the horse.
                        const int32_t painting_idx = find_index(hobbies, Hobby::Painting);
                        const int32_t horse_idx = find_index(pets, Pet::Horse);
                        if (painting_idx == -1 || horse_idx == -1) continue;
                        if ((painting_idx != horse_idx - 1) && (painting_idx != horse_idx + 1)) continue;
                        
                        // 13. The person who plays football drinks orange juice.
                        const int32_t football_idx = find_index(hobbies, Hobby::Football);
                        if (football_idx == -1) continue;
                        if (drinks[football_idx] != Drink::OrangeJuice) continue;
                        
                        // 14. The Japanese person plays chess.
                        const int32_t japanese_idx = find_index(nationalities, Nationality::Japanese);
                        if (japanese_idx == -1) continue;
                        if (hobbies[japanese_idx] != Hobby::Chess) continue;
                        
                        // 15. The Norwegian lives next to the blue house.
                        const int32_t blue_idx = find_index(colors, Color::Blue);
                        if (blue_idx == -1) continue;
                        if ((blue_idx != 1) && (blue_idx != -1)) continue; // Norwegian is at index 0, so next to means index 1
                        // Actually, index 0 is next to index 1 only
                        if (blue_idx != 1) continue;
                        
                        // All constraints are satisfied
                        const int32_t water_idx = find_index(drinks, Drink::Water);
                        const int32_t zebra_idx = find_index(pets, Pet::Zebra);
                        
                        // Convert to string
                        const array<string, 5> nationality_names = {
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
                        };
                        
                        solution.drinksWater = nationality_names[static_cast<int32_t>(nationalities[water_idx])];
                        solution.ownsZebra = nationality_names[static_cast<int32_t>(nationalities[zebra_idx])];
                        return solution;
                    } while (next_permutation(hobbies.begin(), hobbies.end()));
                } while (next_permutation(pets.begin(), pets.end()));
            } while (next_permutation(colors.begin(), colors.end()));
        } while (next_permutation(drinks.begin(), drinks.end()));
    } while (next_permutation(nationalities.begin(), nationalities.end()));
    
    return solution;
}

}  // namespace zebra_puzzle
