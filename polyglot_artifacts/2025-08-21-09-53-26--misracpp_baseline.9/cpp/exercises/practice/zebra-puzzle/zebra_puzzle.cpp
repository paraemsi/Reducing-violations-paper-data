#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

using std::array;
using std::string;
using std::vector;

// All possible values for each attribute
const array<string, 5> COLORS    = {"red", "green", "ivory", "yellow", "blue"};
const array<string, 5> NATIONALS = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const array<string, 5> PETS      = {"dog", "snails", "fox", "horse", "zebra"};
const array<string, 5> DRINKS    = {"coffee", "tea", "milk", "orange juice", "water"};
const array<string, 5> HOBBIES   = {"dancing", "reading", "painting", "chess", "football"};

// Helper function to get the index of a value in an array
template <size_t N>
int index_of(const array<string, N>& arr, const string& value) {
    for (size_t i = 0; i < N; ++i)
        if (arr[i] == value) return static_cast<int>(i);
    return -1;
}

struct House {
    string color;
    string nationality;
    string pet;
    string drink;
    string hobby;
};

bool is_valid(const array<House, 5>& houses) {
    // 2. The Englishman lives in the red house.
    for (const auto& h : houses)
        if (h.nationality == "Englishman" && h.color != "red")
            return false;

    // 3. The Spaniard owns the dog.
    for (const auto& h : houses)
        if (h.nationality == "Spaniard" && h.pet != "dog")
            return false;

    // 4. The person in the green house drinks coffee.
    for (const auto& h : houses)
        if (h.color == "green" && h.drink != "coffee")
            return false;

    // 5. The Ukrainian drinks tea.
    for (const auto& h : houses)
        if (h.nationality == "Ukrainian" && h.drink != "tea")
            return false;

    // 6. The green house is immediately to the right of the ivory house.
    for (int i = 0; i < 4; ++i)
        if (houses[i].color == "ivory" && houses[i+1].color != "green")
            return false;
    for (int i = 1; i < 5; ++i)
        if (houses[i].color == "green" && houses[i-1].color != "ivory")
            return false;

    // 7. The snail owner likes to go dancing.
    for (const auto& h : houses)
        if (h.pet == "snails" && h.hobby != "dancing")
            return false;

    // 8. The person in the yellow house is a painter.
    for (const auto& h : houses)
        if (h.color == "yellow" && h.hobby != "painting")
            return false;

    // 9. The person in the middle house drinks milk.
    if (houses[2].drink != "milk")
        return false;

    // 10. The Norwegian lives in the first house.
    if (houses[0].nationality != "Norwegian")
        return false;

    // 11. The person who enjoys reading lives in the house next to the person with the fox.
    {
        bool found = false;
        for (int i = 0; i < 5; ++i) {
            if (houses[i].hobby == "reading") {
                if ((i > 0 && houses[i-1].pet == "fox") ||
                    (i < 4 && houses[i+1].pet == "fox")) {
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }

    // 12. The painter's house is next to the house with the horse.
    {
        bool found = false;
        for (int i = 0; i < 5; ++i) {
            if (houses[i].hobby == "painting") {
                if ((i > 0 && houses[i-1].pet == "horse") ||
                    (i < 4 && houses[i+1].pet == "horse")) {
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }

    // 13. The person who plays football drinks orange juice.
    for (const auto& h : houses)
        if (h.hobby == "football" && h.drink != "orange juice")
            return false;

    // 14. The Japanese person plays chess.
    for (const auto& h : houses)
        if (h.nationality == "Japanese" && h.hobby != "chess")
            return false;

    // 15. The Norwegian lives next to the blue house.
    {
        int nor_idx = -1;
        for (int i = 0; i < 5; ++i)
            if (houses[i].nationality == "Norwegian")
                nor_idx = i;
        if (!((nor_idx > 0 && houses[nor_idx-1].color == "blue") ||
              (nor_idx < 4 && houses[nor_idx+1].color == "blue")))
            return false;
    }

    return true;
}

Solution solve() {
    array<string, 5> colors    = COLORS;
    array<string, 5> nationals = NATIONALS;
    array<string, 5> pets      = PETS;
    array<string, 5> drinks    = DRINKS;
    array<string, 5> hobbies   = HOBBIES;

    // Fix clues that pin down positions to reduce search space
    // Norwegian in first house
    std::swap(nationals[0], nationals[index_of(nationals, "Norwegian")]);
    // Milk in middle house
    std::swap(drinks[2], drinks[index_of(drinks, "milk")]);

    do {
        // Norwegian in first house
        if (nationals[0] != "Norwegian") continue;
        do {
            // Milk in middle house
            if (drinks[2] != "milk") continue;
            do {
                do {
                    do {
                        array<House, 5> houses;
                        for (int i = 0; i < 5; ++i) {
                            houses[i] = House{
                                colors[i],
                                nationals[i],
                                pets[i],
                                drinks[i],
                                hobbies[i]
                            };
                        }
                        if (is_valid(houses)) {
                            string water_drinker, zebra_owner;
                            for (const auto& h : houses) {
                                if (h.drink == "water")
                                    water_drinker = h.nationality;
                                if (h.pet == "zebra")
                                    zebra_owner = h.nationality;
                            }
                            return Solution{water_drinker, zebra_owner};
                        }
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationals.begin() + 1, nationals.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    // If no solution found
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
