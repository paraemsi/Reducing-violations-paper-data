#include "zebra_puzzle.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace zebra_puzzle {

Solution solve() {
    enum Nationality { ENGLISHMAN, SPANIARD, UKRAINIAN, NORWEGIAN, JAPANESE };
    enum Color { RED, GREEN, IVORY, YELLOW, BLUE };
    enum Pet { DOG, SNAILS, FOX, HORSE, ZEBRA };
    enum Drink { COFFEE, TEA, MILK, ORANGE_JUICE, WATER };
    enum Hobby { DANCING, PAINTER, READING, FOOTBALL, CHESS };

    const std::string nationalities_str[] = {"Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

    std::vector<int> p(5);
    std::iota(p.begin(), p.end(), 0);

    auto colors = p;
    do {
        if (colors[1] != BLUE) continue;

        auto green_pos_it = std::find(colors.begin(), colors.end(), GREEN);
        auto ivory_pos_it = std::find(colors.begin(), colors.end(), IVORY);
        if (green_pos_it - ivory_pos_it != 1) continue;

        auto nationalities = p;
        do {
            if (nationalities[0] != NORWEGIAN) continue;
            
            auto red_pos = std::distance(colors.begin(), std::find(colors.begin(), colors.end(), RED));
            if (nationalities[red_pos] != ENGLISHMAN) continue;

            auto drinks = p;
            do {
                if (drinks[2] != MILK) continue;

                auto green_pos = std::distance(colors.begin(), green_pos_it);
                if (drinks[green_pos] != COFFEE) continue;

                auto ukr_pos = std::distance(nationalities.begin(), std::find(nationalities.begin(), nationalities.end(), UKRAINIAN));
                if (drinks[ukr_pos] != TEA) continue;

                auto hobbies = p;
                do {
                    auto yellow_pos = std::distance(colors.begin(), std::find(colors.begin(), colors.end(), YELLOW));
                    if (hobbies[yellow_pos] != PAINTER) continue;
                    
                    auto football_pos = std::distance(hobbies.begin(), std::find(hobbies.begin(), hobbies.end(), FOOTBALL));
                    if (drinks[football_pos] != ORANGE_JUICE) continue;

                    auto jap_pos = std::distance(nationalities.begin(), std::find(nationalities.begin(), nationalities.end(), JAPANESE));
                    if (hobbies[jap_pos] != CHESS) continue;

                    auto pets = p;
                    do {
                        auto spa_pos = std::distance(nationalities.begin(), std::find(nationalities.begin(), nationalities.end(), SPANIARD));
                        if (pets[spa_pos] != DOG) continue;
                        
                        auto snails_pos = std::distance(pets.begin(), std::find(pets.begin(), pets.end(), SNAILS));
                        if (hobbies[snails_pos] != DANCING) continue;
                        
                        auto reading_pos = std::distance(hobbies.begin(), std::find(hobbies.begin(), hobbies.end(), READING));
                        auto fox_pos = std::distance(pets.begin(), std::find(pets.begin(), pets.end(), FOX));
                        if (std::abs(reading_pos - fox_pos) != 1) continue;
                        
                        auto painter_pos = std::distance(hobbies.begin(), std::find(hobbies.begin(), hobbies.end(), PAINTER));
                        auto horse_pos = std::distance(pets.begin(), std::find(pets.begin(), pets.end(), HORSE));
                        if (std::abs(painter_pos - horse_pos) != 1) continue;
                        
                        auto water_drinker_pos = std::distance(drinks.begin(), std::find(drinks.begin(), drinks.end(), WATER));
                        auto zebra_owner_pos = std::distance(pets.begin(), std::find(pets.begin(), pets.end(), ZEBRA));
                        
                        return {nationalities_str[nationalities[water_drinker_pos]], nationalities_str[nationalities[zebra_owner_pos]]};

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    return {};
}

}  // namespace zebra_puzzle
