#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <cstdlib>     // for std::abs

namespace zebra_puzzle {

namespace {
 // helper to find position of a value (enum or int) in a fixed size
 // std::array<int, N>. Enumerations convert to int automatically.
template <std::size_t N>
int pos_of(const std::array<int, N>& arr, int value) {
    for (std::size_t i = 0; i < N; ++i) {
        if (arr[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;  // should never happen for correct permutations
}
}  // namespace

Solution solve() {
    // Enumerations for all attributes
    enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Nat { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Pet { DOG, SNAIL, FOX, HORSE, ZEBRA };
    enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby { DANCING, PAINTING, READING, FOOTBALL, CHESS };

    const std::array<std::string, 5> nat_to_str{
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    // Base permutation {0,1,2,3,4}
    std::array<int, 5> base{0, 1, 2, 3, 4};

    // Iterate over color permutations first (120)
    std::array<int, 5> colors{};
    std::array<int, 5> nats{};
    std::array<int, 5> drinks{};
    std::array<int, 5> pets{};
    std::array<int, 5> hobbies{};

    std::array<int, 5> color_perm = base;
    do {
        colors = color_perm;

        // (6) Green immediately right of Ivory
        int pos_green  = pos_of(colors, GREEN);
        int pos_ivory  = pos_of(colors, IVORY);
        if (pos_green != pos_ivory + 1) continue;

        int pos_red   = pos_of(colors, RED);
        // int pos_yellow = pos_of(colors, YELLOW);  // removed: unused variable
        int pos_blue   = pos_of(colors, BLUE);

        // Nationalities permutation
        std::array<int, 5> nat_perm = base;
        do {
            nats = nat_perm;

            // (2) Englishman lives in red house
            if (pos_of(nats, ENGLISHMAN) != pos_red) continue;

            // (10) Norwegian lives in first house
            if (pos_of(nats, NORWEGIAN) != 0) continue;

            // (15) Norwegian lives next to blue house
            if (std::abs(pos_of(nats, NORWEGIAN) - pos_blue) != 1) continue;

            // Drinks permutation
            std::array<int, 5> drink_perm = base;
            do {
                drinks = drink_perm;

                // (4) Green house drinks coffee
                if (pos_of(drinks, COFFEE) != pos_green) continue;

                // (5) Ukrainian drinks tea
                if (pos_of(nats, UKRAINIAN) != pos_of(drinks, TEA)) continue;

                // (9) Middle house drinks milk
                if (pos_of(drinks, MILK) != 2) continue;

                // Pets permutation
                std::array<int, 5> pet_perm = base;
                do {
                    pets = pet_perm;

                    // (3) Spaniard owns dog
                    if (pos_of(nats, SPANIARD) != pos_of(pets, DOG)) continue;

                    // Hobbies permutation
                    std::array<int, 5> hobby_perm = base;
                    do {
                        hobbies = hobby_perm;

                        // (7) Snail owner likes dancing
                        if (pos_of(pets, SNAIL) != pos_of(hobbies, DANCING)) continue;

                        // (8) Yellow house painter
                        if (pos_of(colors, YELLOW) != pos_of(hobbies, PAINTING)) continue;

                        // (12) Painter's house next to horse owner
                        if (std::abs(pos_of(hobbies, PAINTING) - pos_of(pets, HORSE)) != 1) continue;

                        // (11) Reading next to fox owner
                        if (std::abs(pos_of(hobbies, READING) - pos_of(pets, FOX)) != 1) continue;

                        // (13) Football drinks orange juice
                        if (pos_of(hobbies, FOOTBALL) != pos_of(drinks, ORANGE_JUICE)) continue;

                        // (14) Japanese plays chess
                        if (pos_of(nats, JAPANESE) != pos_of(hobbies, CHESS)) continue;

                        // All constraints satisfied -> build solution
                        int water_pos = pos_of(drinks, WATER);
                        int zebra_pos = pos_of(pets, ZEBRA);

                        return Solution{nat_to_str[static_cast<std::size_t>(nats[water_pos])],
                                        nat_to_str[static_cast<std::size_t>(nats[zebra_pos])]};
                    } while (std::next_permutation(hobby_perm.begin(), hobby_perm.end()));
                } while (std::next_permutation(pet_perm.begin(), pet_perm.end()));
            } while (std::next_permutation(drink_perm.begin(), drink_perm.end()));
        } while (std::next_permutation(nat_perm.begin(), nat_perm.end()));
    } while (std::next_permutation(color_perm.begin(), color_perm.end()));

    // Fallback (the puzzle guarantees a solution, but keep compiler happy)
    return {};
}

}  // namespace zebra_puzzle
