#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

namespace zebra_puzzle {

using namespace std;

enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

bool satisfiesConstraints(const array<House, 5>& houses) {
    // Check all constraints
    for (int i = 0; i < 5; i++) {
        const auto& h = houses[i];
        
        // 2. Englishman in red house
        if (h.nationality == Nationality::Englishman && h.color != Color::Red)
            return false;
        // 3. Spaniard owns dog
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog)
            return false;
        // 4. Green house drinks coffee
        if (h.color == Color::Green && h.drink != Drink::Coffee)
            return false;
        // 5. Ukrainian drinks tea
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea)
            return false;
        // 8. Yellow house is painter
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting)
            return false;
        // 13. Football player drinks orange juice
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice)
            return false;
        // 14. Japanese plays chess
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess)
            return false;
    }
    
    // Check constraints that require comparing houses
    // 6. Green is immediately right of ivory
    bool found = false;
    for (int i = 1; i < 5; i++) {
        if (houses[i].color == Color::Green && houses[i-1].color == Color::Ivory) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    
    // 7. Snail owner likes dancing
    // 9. Middle house drinks milk (checked during generation)
    if (houses[2].drink != Drink::Milk) return false;
    // 10. Norwegian in first house
    if (houses[0].nationality != Nationality::Norwegian) return false;
    // 11. Reader next to fox owner
    // 12. Painter next to horse owner
    // 15. Norwegian next to blue house
    
    // Check neighbor constraints
    for (int i = 0; i < 5; i++) {
        // 11. Reader next to fox owner
        if (houses[i].hobby == Hobby::Reading) {
            bool adjacent = false;
            if (i > 0 && houses[i-1].pet == Pet::Fox) adjacent = true;
            if (i < 4 && houses[i+1].pet == Pet::Fox) adjacent = true;
            if (!adjacent) return false;
        }
        // 12. Painter next to horse owner
        if (houses[i].hobby == Hobby::Painting) {
            bool adjacent = false;
            if (i > 0 && houses[i-1].pet == Pet::Horse) adjacent = true;
            if (i < 4 && houses[i+1].pet == Pet::Horse) adjacent = true;
            if (!adjacent) return false;
        }
        // 15. Norwegian next to blue house
        if (houses[i].nationality == Nationality::Norwegian) {
            bool adjacent = false;
            if (i > 0 && houses[i-1].color == Color::Blue) adjacent = true;
            if (i < 4 && houses[i+1].color == Color::Blue) adjacent = true;
            if (!adjacent) return false;
        }
        // 7. Snail owner likes dancing
        if (houses[i].pet == Pet::Snails && houses[i].hobby != Hobby::Dancing)
            return false;
    }
    
    return true;
}

Solution solve() {
    array<House, 5> houses;
    Solution solution;
    
    // Track which values are used for each category
    array<bool, 5> usedColor{};
    array<bool, 5> usedNationality{};
    array<bool, 5> usedPet{};
    array<bool, 5> usedDrink{};
    array<bool, 5> usedHobby{};
    
    // Helper lambda to check constraints up to the current house
    std::function<bool(int)> isValid = [&](int houseIndex) -> bool {
        const auto& h = houses[houseIndex];
        
        // Check all constraints that involve the current house
        // 2. Englishman in red house
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. Spaniard owns dog
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. Green house drinks coffee
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. Ukrainian drinks tea
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 6. Green is immediately right of ivory
        if (houseIndex > 0 && houses[houseIndex].color == Color::Green && houses[houseIndex - 1].color != Color::Ivory) return false;
        if (houseIndex < 4 && houses[houseIndex].color == Color::Ivory && houses[houseIndex + 1].color != Color::Green) return false;
        // 7. Snail owner likes dancing
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. Yellow house is painter
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 9. Middle house drinks milk
        if (houseIndex == 2 && h.drink != Drink::Milk) return false;
        // 10. Norwegian in first house
        if (houseIndex == 0 && h.nationality != Nationality::Norwegian) return false;
        // 13. Football player drinks orange juice
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. Japanese plays chess
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
        // 15. Norwegian next to blue house
        if (h.nationality == Nationality::Norwegian) {
            if (houseIndex == 0 && houses[1].color != Color::Blue) return false;
            if (houseIndex == 4 && houses[3].color != Color::Blue) return false;
            if (houseIndex > 0 && houseIndex < 4) {
                if (houses[houseIndex - 1].color != Color::Blue && houses[houseIndex + 1].color != Color::Blue) return false;
            }
        }
        
        // Check neighbor constraints that can be partially checked
        // These are tricky to check until adjacent houses are filled
        return true;
    };
    
    // Recursive backtracking function
    std::function<bool(int)> backtrack = [&](int houseIndex) -> bool {
        if (houseIndex == 5) {
            // Check remaining constraints that involve multiple houses
            // 11. Reader next to fox owner
            for (int i = 0; i < 5; i++) {
                if (houses[i].hobby == Hobby::Reading) {
                    bool found = false;
                    if (i > 0 && houses[i - 1].pet == Pet::Fox) found = true;
                    if (i < 4 && houses[i + 1].pet == Pet::Fox) found = true;
                    if (!found) return false;
                }
            }
            // 12. Painter next to horse owner
            for (int i = 0; i < 5; i++) {
                if (houses[i].hobby == Hobby::Painting) {
                    bool found = false;
                    if (i > 0 && houses[i - 1].pet == Pet::Horse) found = true;
                    if (i < 4 && houses[i + 1].pet == Pet::Horse) found = true;
                    if (!found) return false;
                }
            }
            return true;
        }
        
        // Try all possible assignments for the current house
        for (int c = 0; c < 5; c++) { if (usedColor[c]) continue;
        for (int n = 0; n < 5; n++) { if (usedNationality[n]) continue;
        for (int p = 0; p < 5; p++) { if (usedPet[p]) continue;
        for (int d = 0; d < 5; d++) { if (usedDrink[d]) continue;
        for (int h = 0; h < 5; h++) { if (usedHobby[h]) continue;
            houses[houseIndex] = {
                static_cast<Color>(c),
                static_cast<Nationality>(n),
                static_cast<Pet>(p),
                static_cast<Drink>(d),
                static_cast<Hobby>(h)
            };
            
            if (isValid(houseIndex)) {
                usedColor[c] = usedNationality[n] = usedPet[p] = usedDrink[d] = usedHobby[h] = true;
                if (backtrack(houseIndex + 1)) return true;
                usedColor[c] = usedNationality[n] = usedPet[p] = usedDrink[d] = usedHobby[h] = false;
            }
        }}}}}
        return false;
    };
    
    if (backtrack(0)) {
        for (int i = 0; i < 5; i++) {
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
    
    throw runtime_error("No solution found");
}

}  // namespace zebra_puzzle
