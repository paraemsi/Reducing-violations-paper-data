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

bool is_next_to(int a, int b) {
    return std::abs(a - b) == 1;
}

bool is_right_of(int a, int b) {
    return a - b == 1;
}

} // namespace

Solution solve() {
    std::array<int, N> color_perm, nat_perm, pet_perm, drink_perm, hobby_perm;
    for (int i = 0; i < N; ++i) {
        color_perm[i] = nat_perm[i] = pet_perm[i] = drink_perm[i] = hobby_perm[i] = i;
    }

    // To reduce search space, fix some clues:
    // - Norwegian lives in first house (nat_perm[0] == Norwegian)
    // - Milk is drunk in the middle house (drink_perm[2] == milk)
    // - Green is immediately right of ivory (color_perm[green] == color_perm[ivory] + 1)
    // - Norwegian lives next to blue (color_perm[blue] == 1 or color_perm[blue] == -1)
    // - etc.

    do { // color
        // Green is immediately right of ivory
        int green = std::find(colors.begin(), colors.end(), "green") - colors.begin();
        int ivory = std::find(colors.begin(), colors.end(), "ivory") - colors.begin();
        if (!is_right_of(std::find(color_perm.begin(), color_perm.end(), green) - color_perm.begin(),
                         std::find(color_perm.begin(), color_perm.end(), ivory) - color_perm.begin()))
            continue;

        // Norwegian lives next to blue
        int blue = std::find(colors.begin(), colors.end(), "blue") - colors.begin();
        int blue_pos = std::find(color_perm.begin(), color_perm.end(), blue) - color_perm.begin();
        int nor_pos = 0; // Norwegian must be in first house
        if (!is_next_to(blue_pos, nor_pos))
            continue;

        do { // nationality
            // Norwegian in first house
            int norwegian = std::find(nationalities.begin(), nationalities.end(), "Norwegian") - nationalities.begin();
            if (nat_perm[0] != norwegian)
                continue;

            // Englishman lives in red house
            int englishman = std::find(nationalities.begin(), nationalities.end(), "Englishman") - nationalities.begin();
            int red = std::find(colors.begin(), colors.end(), "red") - colors.begin();
            int red_pos = std::find(color_perm.begin(), color_perm.end(), red) - color_perm.begin();
            int eng_pos = std::find(nat_perm.begin(), nat_perm.end(), englishman) - nat_perm.begin();
            if (eng_pos != red_pos)
                continue;

            // Japanese plays chess
            int japanese = std::find(nationalities.begin(), nationalities.end(), "Japanese") - nationalities.begin();

            do { // pet
                // Spaniard owns the dog
                int spaniard = std::find(nationalities.begin(), nationalities.end(), "Spaniard") - nationalities.begin();
                int dog = std::find(pets.begin(), pets.end(), "dog") - pets.begin();
                int spaniard_pos = std::find(nat_perm.begin(), nat_perm.end(), spaniard) - nat_perm.begin();
                int dog_pos = std::find(pet_perm.begin(), pet_perm.end(), dog) - pet_perm.begin();
                if (spaniard_pos != dog_pos)
                    continue;

                do { // drink
                    // Coffee in green house
                    int coffee = std::find(drinks.begin(), drinks.end(), "coffee") - drinks.begin();
                    int green_pos = std::find(color_perm.begin(), color_perm.end(), green) - color_perm.begin();
                    int coffee_pos = std::find(drink_perm.begin(), drink_perm.end(), coffee) - drink_perm.begin();
                    if (green_pos != coffee_pos)
                        continue;

                    // Ukrainian drinks tea
                    int ukrainian = std::find(nationalities.begin(), nationalities.end(), "Ukrainian") - nationalities.begin();
                    int tea = std::find(drinks.begin(), drinks.end(), "tea") - drinks.begin();
                    int ukr_pos = std::find(nat_perm.begin(), nat_perm.end(), ukrainian) - nat_perm.begin();
                    int tea_pos = std::find(drink_perm.begin(), drink_perm.end(), tea) - drink_perm.begin();
                    if (ukr_pos != tea_pos)
                        continue;

                    // Milk in middle house
                    int milk = std::find(drinks.begin(), drinks.end(), "milk") - drinks.begin();
                    if (drink_perm[2] != milk)
                        continue;

                    do { // hobby
                        // Snail owner likes dancing
                        int snails = std::find(pets.begin(), pets.end(), "snails") - pets.begin();
                        int dancing = std::find(hobbies.begin(), hobbies.end(), "dancing") - hobbies.begin();
                        int snails_pos = std::find(pet_perm.begin(), pet_perm.end(), snails) - pet_perm.begin();
                        int dancing_pos = std::find(hobby_perm.begin(), hobby_perm.end(), dancing) - hobby_perm.begin();
                        if (snails_pos != dancing_pos)
                            continue;

                        // Yellow house is painter
                        int yellow = std::find(colors.begin(), colors.end(), "yellow") - colors.begin();
                        int painting = std::find(hobbies.begin(), hobbies.end(), "painting") - hobbies.begin();
                        int yellow_pos = std::find(color_perm.begin(), color_perm.end(), yellow) - color_perm.begin();
                        int painting_pos = std::find(hobby_perm.begin(), hobby_perm.end(), painting) - hobby_perm.begin();
                        if (yellow_pos != painting_pos)
                            continue;

                        // Japanese plays chess
                        int chess = std::find(hobbies.begin(), hobbies.end(), "chess") - hobbies.begin();
                        int jap_pos = std::find(nat_perm.begin(), nat_perm.end(), japanese) - nat_perm.begin();
                        int chess_pos = std::find(hobby_perm.begin(), hobby_perm.end(), chess) - hobby_perm.begin();
                        if (jap_pos != chess_pos)
                            continue;

                        // Football drinks orange juice
                        int football = std::find(hobbies.begin(), hobbies.end(), "football") - hobbies.begin();
                        int orange_juice = std::find(drinks.begin(), drinks.end(), "orange juice") - drinks.begin();
                        int football_pos = std::find(hobby_perm.begin(), hobby_perm.end(), football) - hobby_perm.begin();
                        int oj_pos = std::find(drink_perm.begin(), drink_perm.end(), orange_juice) - drink_perm.begin();
                        if (football_pos != oj_pos)
                            continue;

                        // Reading next to fox
                        int reading = std::find(hobbies.begin(), hobbies.end(), "reading") - hobbies.begin();
                        int fox = std::find(pets.begin(), pets.end(), "fox") - pets.begin();
                        int reading_pos = std::find(hobby_perm.begin(), hobby_perm.end(), reading) - hobby_perm.begin();
                        int fox_pos = std::find(pet_perm.begin(), pet_perm.end(), fox) - pet_perm.begin();
                        if (!is_next_to(reading_pos, fox_pos))
                            continue;

                        // Painter's house next to horse
                        int horse = std::find(pets.begin(), pets.end(), "horse") - pets.begin();
                        int painter_pos = painting_pos;
                        int horse_pos = std::find(pet_perm.begin(), pet_perm.end(), horse) - pet_perm.begin();
                        if (!is_next_to(painter_pos, horse_pos))
                            continue;

                        // All constraints satisfied, build solution
                        std::vector<House> houses(N);
                        for (int i = 0; i < N; ++i) {
                            houses[i].color = colors[color_perm[i]];
                            houses[i].nationality = nationalities[nat_perm[i]];
                            houses[i].pet = pets[pet_perm[i]];
                            houses[i].drink = drinks[drink_perm[i]];
                            houses[i].hobby = hobbies[hobby_perm[i]];
                        }

                        std::string drinksWater, ownsZebra;
                        for (const auto& h : houses) {
                            if (h.drink == "water")
                                drinksWater = h.nationality;
                            if (h.pet == "zebra")
                                ownsZebra = h.nationality;
                        }
                        return Solution{drinksWater, ownsZebra};

                    } while (std::next_permutation(hobby_perm.begin(), hobby_perm.end()));
                } while (std::next_permutation(drink_perm.begin(), drink_perm.end()));
            } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
        } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));
    } while (std::next_permutation(color_perm.begin(), color_perm.end()));

    // If no solution found
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
