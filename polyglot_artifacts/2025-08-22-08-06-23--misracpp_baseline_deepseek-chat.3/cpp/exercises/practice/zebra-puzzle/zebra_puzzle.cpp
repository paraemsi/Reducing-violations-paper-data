#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <optional>
using namespace std;

namespace zebra_puzzle {

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

array<House, 5> solution;

// Check if all constraints are satisfied
bool is_valid(const array<House, 5>& houses) {
    // Check each constraint
    for (int i = 0; i < 5; i++) {
        // 2. The Englishman lives in the red house.
        if (houses[i].nationality == Nationality::Englishman && houses[i].color != Color::Red)
            return false;
        // 3. The Spaniard owns the dog.
        if (houses[i].nationality == Nationality::Spaniard && houses[i].pet != Pet::Dog)
            return false;
        // 4. The person in the green house drinks coffee.
        if (houses[i].color == Color::Green && houses[i].drink != Drink::Coffee)
            return false;
        // 5. The Ukrainian drinks tea.
        if (houses[i].nationality == Nationality::Ukrainian && houses[i].drink != Drink::Tea)
            return false;
        // 8. The person in the yellow house is a painter.
        if (houses[i].color == Color::Yellow && houses[i].hobby != Hobby::Painting)
            return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && houses[i].drink != Drink::Milk)
            return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && houses[i].nationality != Nationality::Norwegian)
            return false;
        // 13. The person who plays football drinks orange juice.
        if (houses[i].hobby == Hobby::Football && houses[i].drink != Drink::OrangeJuice)
            return false;
        // 14. The Japanese person plays chess.
        if (houses[i].nationality == Nationality::Japanese && houses[i].hobby != Hobby::Chess)
            return false;
    }
    
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (houses[i].color == Color::Ivory && houses[i + 1].color == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; i++) {
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing)
            return false;
    }
    
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].pet == Pet::Fox) adjacent = true;
            if (i < 4 && houses[i + 1].pet == Pet::Fox) adjacent = true;
            if (!adjacent) return false;
            break;
        }
    }
    
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].pet == Pet::Horse) adjacent = true;
            if (i < 4 && houses[i + 1].pet == Pet::Horse) adjacent = true;
            if (!adjacent) return false;
            break;
        }
    }
    
    // 15. The Norwegian lives next to the blue house.
    for (int i = 0; i < 5; i++) {
        if (houses[i].nationality == Nationality::Norwegian) {
            bool adjacent = false;
            if (i > 0 && houses[i - 1].color == Color::Blue) adjacent = true;
            if (i < 4 && houses[i + 1].color == Color::Blue) adjacent = true;
            if (!adjacent) return false;
            break;
        }
    }
    
    return true;
}

// Generate all permutations and find the valid solution
template<typename T>
void generate_permutations(vector<T> items, int index, function<void(const vector<T>&)> callback) {
    if (index == items.size() - 1) {
        callback(items);
        return;
    }
    for (int i = index; i < items.size(); i++) {
        swap(items[index], items[i]);
        generate_permutations(items, index + 1, callback);
        swap(items[index], items[i]);
    }
}

Solution solve() {
    // Generate all possible permutations for each category
    vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, 
                                        Nationality::Norwegian, Nationality::Japanese};
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // We know the Norwegian is in the first house and milk is in the middle
    // This can be used to optimize, but for now, let's generate all
    
    generate_permutations<Color>(colors, 0, [&](const vector<Color>& color_perm) {
        generate_permutations<Nationality>(nationalities, 0, [&](const vector<Nationality>& nationality_perm) {
            // Check if Norwegian is in first house
            if (nationality_perm[0] != Nationality::Norwegian) return;
            
            generate_permutations<Drink>(drinks, 0, [&](const vector<Drink>& drink_perm) {
                // Check if milk is in middle house
                if (drink_perm[2] != Drink::Milk) return;
                
                generate_permutations<Pet>(pets, 0, [&](const vector<Pet>& pet_perm) {
                    generate_permutations<Hobby>(hobbies, 0, [&](const vector<Hobby>& hobby_perm) {
                        array<House, 5> candidate;
                        for (int i = 0; i < 5; i++) {
                            candidate[i] = {color_perm[i], nationality_perm[i], drink_perm[i], pet_perm[i], hobby_perm[i]};
                        }
                        if (is_valid(candidate)) {
                            solution = candidate;
                        }
                    });
                });
            });
        });
    });
    
    // Find who drinks water and owns the zebra
    string waterDrinker, zebraOwner;
    for (int i = 0; i < 5; i++) {
        if (solution[i].drink == Drink::Water) {
            switch (solution[i].nationality) {
                case Nationality::Englishman: waterDrinker = "Englishman"; break;
                case Nationality::Spaniard: waterDrinker = "Spaniard"; break;
                case Nationality::Ukrainian: waterDrinker = "Ukrainian"; break;
                case Nationality::Norwegian: waterDrinker = "Norwegian"; break;
                case Nationality::Japanese: waterDrinker = "Japanese"; break;
            }
        }
        if (solution[i].pet == Pet::Zebra) {
            switch (solution[i].nationality) {
                case Nationality::Englishman: zebraOwner = "Englishman"; break;
                case Nationality::Spaniard: zebraOwner = "Spaniard"; break;
                case Nationality::Ukrainian: zebraOwner = "Ukrainian"; break;
                case Nationality::Norwegian: zebraOwner = "Norwegian"; break;
                case Nationality::Japanese: zebraOwner = "Japanese"; break;
            }
        }
    }
    
    return Solution{waterDrinker, zebraOwner};
}

}  // namespace zebra_puzzle
