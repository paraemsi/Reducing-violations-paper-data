#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snail, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

constexpr int num_houses = 5;

template <typename T>
using Houses = array<T, num_houses>;

struct Assignment {
    Houses<Color> colors;
    Houses<Nationality> nationalities;
    Houses<Pet> pets;
    Houses<Drink> drinks;
    Houses<Hobby> hobbies;
};

bool is_valid(const Assignment& assignment) {
    const auto& c = assignment.colors;
    const auto& n = assignment.nationalities;
    const auto& p = assignment.pets;
    const auto& d = assignment.drinks;
    const auto& h = assignment.hobbies;
    
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < num_houses; ++i) {
        if (n[i] == Nationality::Englishman && c[i] != Color::Red) return false;
    }
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < num_houses; ++i) {
        if (n[i] == Nationality::Spaniard && p[i] != Pet::Dog) return false;
    }
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < num_houses; ++i) {
        if (c[i] == Color::Green && d[i] != Drink::Coffee) return false;
    }
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < num_houses; ++i) {
        if (n[i] == Nationality::Ukrainian && d[i] != Drink::Tea) return false;
    }
    // 6. The green house is immediately to the right of the ivory house.
    bool found = false;
    for (int i = 1; i < num_houses; ++i) {
        if (c[i] == Color::Green && c[i-1] == Color::Ivory) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < num_houses; ++i) {
        if (p[i] == Pet::Snail && h[i] != Hobby::Dancing) return false;
    }
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < num_houses; ++i) {
        if (c[i] == Color::Yellow && h[i] != Hobby::Painting) return false;
    }
    // 9. The person in the middle house drinks milk.
    if (d[2] != Drink::Milk) return false;
    // 10. The Norwegian lives in the first house.
    if (n[0] != Nationality::Norwegian) return false;
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    bool valid = false;
    for (int i = 0; i < num_houses; ++i) {
        if (h[i] == Hobby::Reading) {
            if ((i > 0 && p[i-1] == Pet::Fox) || (i < num_houses-1 && p[i+1] == Pet::Fox)) {
                valid = true;
                break;
            }
        }
    }
    if (!valid) return false;
    // 12. The painter's house is next to the house with the horse.
    valid = false;
    for (int i = 0; i < num_houses; ++i) {
        if (h[i] == Hobby::Painting) {
            if ((i > 0 && p[i-1] == Pet::Horse) || (i < num_houses-1 && p[i+1] == Pet::Horse)) {
                valid = true;
                break;
            }
        }
    }
    if (!valid) return false;
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < num_houses; ++i) {
        if (h[i] == Hobby::Football && d[i] != Drink::OrangeJuice) return false;
    }
    // 14. The Japanese person plays chess.
    for (int i = 0; i < num_houses; ++i) {
        if (n[i] == Nationality::Japanese && h[i] != Hobby::Chess) return false;
    }
    // 15. The Norwegian lives next to the blue house.
    valid = false;
    if (n[0] == Nationality::Norwegian) {
        if (1 < num_houses && c[1] == Color::Blue) valid = true;
    }
    if (!valid) return false;
    
    return true;
}

void generate_permutations(int index, Assignment& assignment, vector<bool>& used, 
                          const vector<Color>& colors, bool& found, Solution& solution) {
    if (found) return;
    if (index == num_houses) {
        if (is_valid(assignment)) {
            found = true;
            // Find who drinks water and owns zebra
            for (int i = 0; i < num_houses; ++i) {
                if (assignment.drinks[i] == Drink::Water) {
                    switch (assignment.nationalities[i]) {
                        case Nationality::Englishman: solution.drinksWater = "Englishman"; break;
                        case Nationality::Spaniard: solution.drinksWater = "Spaniard"; break;
                        case Nationality::Ukrainian: solution.drinksWater = "Ukrainian"; break;
                        case Nationality::Norwegian: solution.drinksWater = "Norwegian"; break;
                        case Nationality::Japanese: solution.drinksWater = "Japanese"; break;
                    }
                }
                if (assignment.pets[i] == Pet::Zebra) {
                    switch (assignment.nationalities[i]) {
                        case Nationality::Englishman: solution.ownsZebra = "Englishman"; break;
                        case Nationality::Spaniard: solution.ownsZebra = "Spaniard"; break;
                        case Nationality::Ukrainian: solution.ownsZebra = "Ukrainian"; break;
                        case Nationality::Norwegian: solution.ownsZebra = "Norwegian"; break;
                        case Nationality::Japanese: solution.ownsZebra = "Japanese"; break;
                    }
                }
            }
        }
        return;
    }
    
    for (int i = 0; i < num_houses; ++i) {
        if (!used[i]) {
            used[i] = true;
            assignment.colors[index] = colors[i];
            generate_permutations(index + 1, assignment, used, colors, found, solution);
            used[i] = false;
            if (found) return;
        }
    }
}

Solution solve() {
    // Generate all possible assignments and find the valid one
    vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, 
                                        Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    vector<Pet> pets = {Pet::Dog, Pet::Snail, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    // We need to generate all permutations for each category, but this is too slow
    // Let's generate them in a smarter way by fixing some values first
    // For now, we'll generate colors and check other constraints
    
    Assignment assignment;
    // Fix some values based on known constraints to speed up
    assignment.nationalities[0] = Nationality::Norwegian;
    assignment.drinks[2] = Drink::Milk;
    
    vector<bool> used(num_houses, false);
    bool found = false;
    Solution solution;
    
    generate_permutations(0, assignment, used, colors, found, solution);
    return solution;
}

}  // namespace zebra_puzzle
