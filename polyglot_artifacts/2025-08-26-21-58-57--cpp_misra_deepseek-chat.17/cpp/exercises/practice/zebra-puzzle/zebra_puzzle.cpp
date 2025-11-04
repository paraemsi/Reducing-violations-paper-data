#include "zebra_puzzle.h"
#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>

namespace zebra_puzzle {

using namespace std;

// Define the categories
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

struct Assignment {
    array<Nationality, 5> nationalities;
    array<Color, 5> colors;
    array<Drink, 5> drinks;
    array<Pet, 5> pets;
    array<Hobby, 5> hobbies;
};

bool isConsistent(const Assignment& a) {
    // Check all constraints
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < 5; i++) {
        if (a.nationalities[i] == Nationality::Englishman && a.colors[i] != Color::Red) return false;
    }
    // 3. The Spaniard owns the dog.
    for (int i = 0; i < 5; i++) {
        if (a.nationalities[i] == Nationality::Spaniard && a.pets[i] != Pet::Dog) return false;
    }
    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < 5; i++) {
        if (a.colors[i] == Color::Green && a.drinks[i] != Drink::Coffee) return false;
    }
    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < 5; i++) {
        if (a.nationalities[i] == Nationality::Ukrainian && a.drinks[i] != Drink::Tea) return false;
    }
    // 6. The green house is immediately to the right of the ivory house.
    for (int i = 0; i < 4; i++) {
        if (a.colors[i] == Color::Ivory && a.colors[i + 1] != Color::Green) return false;
    }
    // Check if green is never to the right of ivory
    bool found = false;
    for (int i = 0; i < 4; i++) {
        if (a.colors[i] == Color::Ivory && a.colors[i + 1] == Color::Green) {
            found = true;
            break;
        }
    }
    if (!found) return false;
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < 5; i++) {
        if (a.pets[i] == Pet::Snails && a.hobbies[i] != Hobby::Dancing) return false;
    }
    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < 5; i++) {
        if (a.colors[i] == Color::Yellow && a.hobbies[i] != Hobby::Painting) return false;
    }
    // 9. The person in the middle house drinks milk.
    if (a.drinks[2] != Drink::Milk) return false;
    // 10. The Norwegian lives in the first house.
    if (a.nationalities[0] != Nationality::Norwegian) return false;
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    for (int i = 0; i < 5; i++) {
        if (a.hobbies[i] == Hobby::Reading) {
            bool adjacentToFox = false;
            if (i > 0 && a.pets[i - 1] == Pet::Fox) adjacentToFox = true;
            if (i < 4 && a.pets[i + 1] == Pet::Fox) adjacentToFox = true;
            if (!adjacentToFox) return false;
        }
    }
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < 5; i++) {
        if (a.hobbies[i] == Hobby::Painting) {
            bool adjacentToHorse = false;
            if (i > 0 && a.pets[i - 1] == Pet::Horse) adjacentToHorse = true;
            if (i < 4 && a.pets[i + 1] == Pet::Horse) adjacentToHorse = true;
            if (!adjacentToHorse) return false;
        }
    }
    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < 5; i++) {
        if (a.hobbies[i] == Hobby::Football && a.drinks[i] != Drink::OrangeJuice) return false;
    }
    // 14. The Japanese person plays chess.
    for (int i = 0; i < 5; i++) {
        if (a.nationalities[i] == Nationality::Japanese && a.hobbies[i] != Hobby::Chess) return false;
    }
    // 15. The Norwegian lives next to the blue house.
    {
        int norwegianPos = -1;
        for (int i = 0; i < 5; i++) {
            if (a.nationalities[i] == Nationality::Norwegian) {
                norwegianPos = i;
                break;
            }
        }
        bool adjacentToBlue = false;
        if (norwegianPos > 0 && a.colors[norwegianPos - 1] == Color::Blue) adjacentToBlue = true;
        if (norwegianPos < 4 && a.colors[norwegianPos + 1] == Color::Blue) adjacentToBlue = true;
        if (!adjacentToBlue) return false;
    }
    return true;
}

void solveImpl(Assignment& a, int house, vector<bool>& usedNat, vector<bool>& usedCol, 
               vector<bool>& usedDrink, vector<bool>& usedPet, vector<bool>& usedHobby,
               vector<Assignment>& solutions) {
    if (house == 5) {
        if (isConsistent(a)) {
            solutions.push_back(a);
        }
        return;
    }
    
    // Try all possible values for each category at this house
    for (int nat = 0; nat < 5; nat++) {
        if (usedNat[nat]) continue;
        a.nationalities[house] = static_cast<Nationality>(nat);
        usedNat[nat] = true;
        for (int col = 0; col < 5; col++) {
            if (usedCol[col]) continue;
            a.colors[house] = static_cast<Color>(col);
            usedCol[col] = true;
            for (int drink = 0; drink < 5; drink++) {
                if (usedDrink[drink]) continue;
                a.drinks[house] = static_cast<Drink>(drink);
                usedDrink[drink] = true;
                for (int pet = 0; pet < 5; pet++) {
                    if (usedPet[pet]) continue;
                    a.pets[house] = static_cast<Pet>(pet);
                    usedPet[pet] = true;
                    for (int hobby = 0; hobby < 5; hobby++) {
                        if (usedHobby[hobby]) continue;
                        a.hobbies[house] = static_cast<Hobby>(hobby);
                        usedHobby[hobby] = true;
                        solveImpl(a, house + 1, usedNat, usedCol, usedDrink, usedPet, usedHobby, solutions);
                        usedHobby[hobby] = false;
                    }
                    usedPet[pet] = false;
                }
                usedDrink[drink] = false;
            }
            usedCol[col] = false;
        }
        usedNat[nat] = false;
    }
}

Solution solve() {
    Assignment a;
    vector<bool> usedNat(5, false);
    vector<bool> usedCol(5, false);
    vector<bool> usedDrink(5, false);
    vector<bool> usedPet(5, false);
    vector<bool> usedHobby(5, false);
    vector<Assignment> solutions;
    
    solveImpl(a, 0, usedNat, usedCol, usedDrink, usedPet, usedHobby, solutions);
    
    // Find water drinker and zebra owner
    Solution result;
    for (const auto& sol : solutions) {
        for (int i = 0; i < 5; i++) {
            if (sol.drinks[i] == Drink::Water) {
                switch (sol.nationalities[i]) {
                    case Nationality::Englishman: result.drinksWater = "Englishman"; break;
                    case Nationality::Spaniard: result.drinksWater = "Spaniard"; break;
                    case Nationality::Ukrainian: result.drinksWater = "Ukrainian"; break;
                    case Nationality::Norwegian: result.drinksWater = "Norwegian"; break;
                    case Nationality::Japanese: result.drinksWater = "Japanese"; break;
                }
            }
            if (sol.pets[i] == Pet::Zebra) {
                switch (sol.nationalities[i]) {
                    case Nationality::Englishman: result.ownsZebra = "Englishman"; break;
                    case Nationality::Spaniard: result.ownsZebra = "Spaniard"; break;
                    case Nationality::Ukrainian: result.ownsZebra = "Ukrainian"; break;
                    case Nationality::Norwegian: result.ownsZebra = "Norwegian"; break;
                    case Nationality::Japanese: result.ownsZebra = "Japanese"; break;
                }
            }
        }
    }
    return result;
}

}  // namespace zebra_puzzle
