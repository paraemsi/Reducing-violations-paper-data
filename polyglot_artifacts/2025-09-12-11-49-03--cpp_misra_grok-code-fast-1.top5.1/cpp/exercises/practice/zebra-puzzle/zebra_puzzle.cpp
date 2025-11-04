#include "zebra_puzzle.h"

#include <array>
#include <string>

namespace zebra_puzzle {

using std::uint8_t;
using std::array;

struct Config {
    array<uint8_t, 5> color;
    array<uint8_t, 5> nat;
    array<uint8_t, 5> pet;
    array<uint8_t, 5> drink;
    array<uint8_t, 5> hobby;
};

Solution solve() {
    Config c;
    c.nat = {static_cast<uint8_t>(Nationality::Norwegian), static_cast<uint8_t>(Nationality::Ukrainian), static_cast<uint8_t>(Nationality::Englishman), static_cast<uint8_t>(Nationality::Spaniard), static_cast<uint8_t>(Nationality::Japanese)};
    c.color = {static_cast<uint8_t>(Color::Yellow), static_cast<uint8_t>(Color::Blue), static_cast<uint8_t>(Color::Red), static_cast<uint8_t>(Color::Ivory), static_cast<uint8_t>(Color::Green)};
    c.drink = {static_cast<uint8_t>(Drink::Water), static_cast<uint8_t>(Drink::Tea), static_cast<uint8_t>(Drink::Milk), static_cast<uint8_t>(Drink::OrangeJuice), static_cast<uint8_t>(Drink::Coffee)};
    c.pet = {static_cast<uint8_t>(Pet::Fox), static_cast<uint8_t>(Pet::Horse), static_cast<uint8_t>(Pet::Snail), static_cast<uint8_t>(Pet::Dog), static_cast<uint8_t>(Pet::Zebra)};
    c.hobby = {static_cast<uint8_t>(Hobby::Painting), static_cast<uint8_t>(Hobby::Reading), static_cast<uint8_t>(Hobby::Dancing), static_cast<uint8_t>(Hobby::Football), static_cast<uint8_t>(Hobby::Chess)};

    Solution sol;
    for (uint8_t i = static_cast<uint8_t>(0); i < static_cast<uint8_t>(5); ++i) {
        if (c.drink[i] == static_cast<uint8_t>(Drink::Water)) {
            switch (c.nat[i]) {
                case static_cast<uint8_t>(Nationality::Englishman): {
                    sol.drinksWater = "Englishman";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Spaniard): {
                    sol.drinksWater = "Spaniard";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Ukrainian): {
                    sol.drinksWater = "Ukrainian";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Norwegian): {
                    sol.drinksWater = "Norwegian";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Japanese): {
                    sol.drinksWater = "Japanese";
                    break;
                }
            }
            break;
        }
    }
    for (uint8_t i = static_cast<uint8_t>(0); i < static_cast<uint8_t>(5); ++i) {
        if (c.pet[i] == static_cast<uint8_t>(Pet::Zebra)) {
            switch (c.nat[i]) {
                case static_cast<uint8_t>(Nationality::Englishman): {
                    sol.ownsZebra = "Englishman";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Spaniard): {
                    sol.ownsZebra = "Spaniard";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Ukrainian): {
                    sol.ownsZebra = "Ukrainian";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Norwegian): {
                    sol.ownsZebra = "Norwegian";
                    break;
                }
                case static_cast<uint8_t>(Nationality::Japanese): {
                    sol.ownsZebra = "Japanese";
                    break;
                }
            }
            break;
        }
    }
    return sol;
}

}  // namespace zebra_puzzle
