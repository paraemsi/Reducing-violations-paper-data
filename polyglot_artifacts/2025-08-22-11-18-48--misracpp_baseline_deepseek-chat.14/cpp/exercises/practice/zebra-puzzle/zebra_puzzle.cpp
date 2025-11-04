#include "zebra_puzzle.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace zebra_puzzle {

// Define the attributes
enum class Color { Red, Green, Ivory, Yellow, Blue };
enum class Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum class Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Pet { Dog, Snails, Fox, Horse, Zebra };
enum class Hobby { Dancing, Painting, Reading, Football, Chess };

// Convert enums to strings for the result
string nationalityToString(Nationality n) {
    switch (n) {
        case Nationality::Englishman: return "Englishman";
        case Nationality::Spaniard: return "Spaniard";
        case Nationality::Ukrainian: return "Ukrainian";
        case Nationality::Norwegian: return "Norwegian";
        case Nationality::Japanese: return "Japanese";
        default: throw runtime_error("Invalid nationality");
    }
}

string drinkToString(Drink d) {
    switch (d) {
        case Drink::Water: return "water";
        default: throw runtime_error("Not the requested drink");
    }
}

string petToString(Pet p) {
    switch (p) {
        case Pet::Zebra: return "zebra";
        default: throw runtime_error("Not the requested pet");
    }
}

struct House {
    Color color;
    Nationality nationality;
    Drink drink;
    Pet pet;
    Hobby hobby;
};

// Check if the current assignment is valid
bool isValid(const array<House, 5>& houses, int upTo) {
    // Check all constraints that can be checked with the current number of assigned houses
    for (int i = 0; i <= upTo; i++) {
        const auto& h = houses[i];
        
        // 2. The Englishman lives in the red house.
        if (h.nationality == Nationality::Englishman && h.color != Color::Red) return false;
        // 3. The Spaniard owns the dog.
        if (h.nationality == Nationality::Spaniard && h.pet != Pet::Dog) return false;
        // 4. The person in the green house drinks coffee.
        if (h.color == Color::Green && h.drink != Drink::Coffee) return false;
        // 5. The Ukrainian drinks tea.
        if (h.nationality == Nationality::Ukrainian && h.drink != Drink::Tea) return false;
        // 7. The snail owner likes to go dancing.
        if (h.pet == Pet::Snails && h.hobby != Hobby::Dancing) return false;
        // 8. The person in the yellow house is a painter.
        if (h.color == Color::Yellow && h.hobby != Hobby::Painting) return false;
        // 9. The person in the middle house drinks milk.
        if (i == 2 && h.drink != Drink::Milk) return false;
        // 10. The Norwegian lives in the first house.
        if (i == 0 && h.nationality != Nationality::Norwegian) return false;
        // 13. The person who plays football drinks orange juice.
        if (h.hobby == Hobby::Football && h.drink != Drink::OrangeJuice) return false;
        // 14. The Japanese person plays chess.
        if (h.nationality == Nationality::Japanese && h.hobby != Hobby::Chess) return false;
    }
    
    // Check inter-house constraints that can be checked
    // 6. The green house is immediately to the right of the ivory house.
    for (int i = 0; i < upTo; i++) {
        if (houses[i].color == Color::Ivory) {
            if (i == 4) return false;
            if (i + 1 > upTo) continue;
            if (houses[i + 1].color != Color::Green) return false;
        }
    }
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    // 12. The painter's house is next to the house with the horse.
    // 15. The Norwegian lives next to the blue house.
    // These are more complex to check partially, so we'll check them when all houses are assigned
    return true;
}

// Check all constraints including those that need all houses to be assigned
bool checkAllConstraints(const array<House, 5>& houses) {
    if (!isValid(houses, 4)) return false;
    
    // Check remaining constraints that need all houses
    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Reading) {
            bool found = false;
            if (i > 0 && houses[i - 1].pet == Pet::Fox) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Fox) found = true;
            if (!found) return false;
        }
    }
    // 12. The painter's house is next to the house with the horse.
    for (int i = 0; i < 5; i++) {
        if (houses[i].hobby == Hobby::Painting) {
            bool found = false;
            if (i > 0 && houses[i - 1].pet == Pet::Horse) found = true;
            if (i < 4 && houses[i + 1].pet == Pet::Horse) found = true;
            if (!found) return false;
        }
    }
    // 15. The Norwegian lives next to the blue house.
    {
        int norwegianIndex = -1;
        for (int i = 0; i < 5; i++) {
            if (houses[i].nationality == Nationality::Norwegian) {
                norwegianIndex = i;
                break;
            }
        }
        bool found = false;
        if (norwegianIndex > 0 && houses[norwegianIndex - 1].color == Color::Blue) found = true;
        if (norwegianIndex < 4 && houses[norwegianIndex + 1].color == Color::Blue) found = true;
        if (!found) return false;
    }
    return true;
}

// Backtracking function
bool solve(array<House, 5>& houses, int index, 
           vector<Color> colors, vector<Nationality> nationalities,
           vector<Drink> drinks, vector<Pet> pets, vector<Hobby> hobbies) {
    if (index == 5) {
        return checkAllConstraints(houses);
    }
    
    for (int i = 0; i < colors.size(); i++) {
        houses[index].color = colors[i];
        auto newColors = colors;
        newColors.erase(newColors.begin() + i);
        for (int j = 0; j < nationalities.size(); j++) {
            houses[index].nationality = nationalities[j];
            auto newNationalities = nationalities;
            newNationalities.erase(newNationalities.begin() + j);
            for (int k = 0; k < drinks.size(); k++) {
                houses[index].drink = drinks[k];
                auto newDrinks = drinks;
                newDrinks.erase(newDrinks.begin() + k);
                for (int l = 0; l < pets.size(); l++) {
                    houses[index].pet = pets[l];
                    auto newPets = pets;
                    newPets.erase(newPets.begin() + l);
                    for (int m = 0; m < hobbies.size(); m++) {
                        houses[index].hobby = hobbies[m];
                        auto newHobbies = hobbies;
                        newHobbies.erase(newHobbies.begin() + m);
                        
                        if (isValid(houses, index)) {
                            if (solve(houses, index + 1, newColors, newNationalities, newDrinks, newPets, newHobbies)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

Solution solution() {
    array<House, 5> houses;
    vector<Color> colors = {Color::Red, Color::Green, Color::Ivory, Color::Yellow, Color::Blue};
    vector<Nationality> nationalities = {Nationality::Englishman, Nationality::Spaniard, Nationality::Ukrainian, Nationality::Norwegian, Nationality::Japanese};
    vector<Drink> drinks = {Drink::Coffee, Drink::Tea, Drink::Milk, Drink::OrangeJuice, Drink::Water};
    vector<Pet> pets = {Pet::Dog, Pet::Snails, Pet::Fox, Pet::Horse, Pet::Zebra};
    vector<Hobby> hobbies = {Hobby::Dancing, Hobby::Painting, Hobby::Reading, Hobby::Football, Hobby::Chess};
    
    if (solve(houses, 0, colors, nationalities, drinks, pets, hobbies)) {
        // Find who drinks water and owns zebra
        string waterDrinker, zebraOwner;
        for (const auto& house : houses) {
            if (house.drink == Drink::Water) {
                waterDrinker = nationalityToString(house.nationality);
            }
            if (house.pet == Pet::Zebra) {
                zebraOwner = nationalityToString(house.nationality);
            }
        }
        return {waterDrinker, zebraOwner};
    }
    throw runtime_error("No solution found");
}

Solution solution() {
    return solve();
}

}  // namespace zebra_puzzle
