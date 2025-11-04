#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

const std::array<std::string, N> colors = {"red", "green", "ivory", "yellow", "blue"};
const std::array<std::string, N> nationalities = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};
const std::array<std::string, N> pets = {"dog", "snails", "fox", "horse", "zebra"};
const std::array<std::string, N> drinks = {"coffee", "tea", "milk", "orange juice", "water"};
const std::array<std::string, N> hobbies = {"dancing", "reading", "painting", "chess", "football"};

struct House {
    std::string color;
    std::string nationality;
    std::string pet;
    std::string drink;
    std::string hobby;
};

bool is_valid(const std::array<House, N>& houses) {
    // 2. The Englishman lives in the red house.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == "Englishman" && houses[i].color != "red")
            return false;

    // 3. The Spaniard owns the dog.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == "Spaniard" && houses[i].pet != "dog")
            return false;

    // 4. The person in the green house drinks coffee.
    for (int i = 0; i < N; ++i)
        if (houses[i].color == "green" && houses[i].drink != "coffee")
            return false;

    // 5. The Ukrainian drinks tea.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == "Ukrainian" && houses[i].drink != "tea")
            return false;

    // 6. The green house is immediately to the right of the ivory house.
    for (int i = 0; i < N - 1; ++i)
        if (houses[i].color == "ivory" && houses[i + 1].color != "green")
            if (houses[i + 1].color == "green")
                continue;
            else
                return false;
    // 7. The snail owner likes to go dancing.
    for (int i = 0; i < N; ++i)
        if (houses[i].pet == "snails" && houses[i].hobby != "dancing")
            return false;

    // 8. The person in the yellow house is a painter.
    for (int i = 0; i < N; ++i)
        if (houses[i].color == "yellow" && houses[i].hobby != "painting")
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
        for (int i = 0; i < N; ++i) {
            if (houses[i].hobby == "reading") {
                if ((i > 0 && houses[i - 1].pet == "fox") ||
                    (i < N - 1 && houses[i + 1].pet == "fox")) {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return false;
    }

    // 12. The painter's house is next to the house with the horse.
    {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (houses[i].hobby == "painting") {
                if ((i > 0 && houses[i - 1].pet == "horse") ||
                    (i < N - 1 && houses[i + 1].pet == "horse")) {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return false;
    }

    // 13. The person who plays football drinks orange juice.
    for (int i = 0; i < N; ++i)
        if (houses[i].hobby == "football" && houses[i].drink != "orange juice")
            return false;

    // 14. The Japanese person plays chess.
    for (int i = 0; i < N; ++i)
        if (houses[i].nationality == "Japanese" && houses[i].hobby != "chess")
            return false;

    // 15. The Norwegian lives next to the blue house.
    {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (houses[i].nationality == "Norwegian") {
                if ((i > 0 && houses[i - 1].color == "blue") ||
                    (i < N - 1 && houses[i + 1].color == "blue")) {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return false;
    }

    return true;
}

template <typename T>
std::vector<std::array<T, N>> all_permutations(const std::array<T, N>& arr) {
    std::vector<std::array<T, N>> perms;
    std::array<T, N> a = arr;
    std::sort(a.begin(), a.end());
    do {
        perms.push_back(a);
    } while (std::next_permutation(a.begin(), a.end()));
    return perms;
}

} // namespace

Solution solve() {
    // Fix clues that allow us to reduce permutations:
    // - Norwegian in first house
    // - Milk in middle house
    // - Green is immediately right of ivory

    // Generate all permutations for each attribute
    auto color_perms = all_permutations(colors);
    auto nat_perms = all_permutations(nationalities);
    auto pet_perms = all_permutations(pets);
    auto drink_perms = all_permutations(drinks);
    auto hobby_perms = all_permutations(hobbies);

    for (const auto& color : color_perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int ivory_idx = -1, green_idx = -1;
        for (int i = 0; i < N; ++i) {
            if (color[i] == "ivory") ivory_idx = i;
            if (color[i] == "green") green_idx = i;
        }
        if (green_idx != ivory_idx + 1)
            continue;

        for (const auto& nat : nat_perms) {
            if (nat[0] != "Norwegian")
                continue;
            for (const auto& pet : pet_perms) {
                for (const auto& drink : drink_perms) {
                    if (drink[2] != "milk")
                        continue;
                    for (const auto& hobby : hobby_perms) {
                        std::array<House, N> houses;
                        for (int i = 0; i < N; ++i) {
                            houses[i] = House{color[i], nat[i], pet[i], drink[i], hobby[i]};
                        }
                        if (is_valid(houses)) {
                            // Find who drinks water and who owns the zebra
                            std::string drinksWater, ownsZebra;
                            for (int i = 0; i < N; ++i) {
                                if (houses[i].drink == "water")
                                    drinksWater = houses[i].nationality;
                                if (houses[i].pet == "zebra")
                                    ownsZebra = houses[i].nationality;
                            }
                            return Solution{drinksWater, ownsZebra};
                        }
                    }
                }
            }
        }
    }
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
