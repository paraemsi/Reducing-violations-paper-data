#include "zebra_puzzle.h"
#include <array>
#include <algorithm>
#include <string>
#include <vector>

namespace zebra_puzzle {

namespace {

constexpr int N = 5;

enum Color { Red, Green, Ivory, Yellow, Blue };
enum Nationality { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
enum Pet { Dog, Snails, Fox, Horse, Zebra };
enum Drink { Coffee, Tea, Milk, OrangeJuice, Water };
enum Hobby { Reading, Dancing, Painting, Football, Chess };

struct House {
    Color color;
    Nationality nationality;
    Pet pet;
    Drink drink;
    Hobby hobby;
};

using Perm = std::array<int, N>;

template <typename T>
std::vector<Perm> all_permutations() {
    Perm p = {0, 1, 2, 3, 4};
    std::vector<Perm> perms;
    do {
        perms.push_back(p);
    } while (std::next_permutation(p.begin(), p.end()));
    return perms;
}

bool is_next_to(int a, int b) {
    return std::abs(a - b) == 1;
}

bool is_right_of(int a, int b) {
    return a - b == 1;
}

} // namespace

Solution solve() {
    // Generate all permutations for each attribute
    auto color_perms = all_permutations<Color>();
    auto nationality_perms = all_permutations<Nationality>();
    auto pet_perms = all_permutations<Pet>();
    auto drink_perms = all_permutations<Drink>();
    auto hobby_perms = all_permutations<Hobby>();

    for (const auto& colors : color_perms) {
        // 6. The green house is immediately to the right of the ivory house.
        int green = std::find(colors.begin(), colors.end(), Green) - colors.begin();
        int ivory = std::find(colors.begin(), colors.end(), Ivory) - colors.begin();
        if (!is_right_of(green, ivory)) continue;

        for (const auto& nationalities : nationality_perms) {
            // 10. The Norwegian lives in the first house.
            if (nationalities[0] != Norwegian) continue;
            // 15. The Norwegian lives next to the blue house.
            int blue = std::find(colors.begin(), colors.end(), Blue) - colors.begin();
            int norwegian = std::find(nationalities.begin(), nationalities.end(), Norwegian) - nationalities.begin();
            if (!is_next_to(blue, norwegian)) continue;
            // 2. The Englishman lives in the red house.
            int englishman = std::find(nationalities.begin(), nationalities.end(), Englishman) - nationalities.begin();
            int red = std::find(colors.begin(), colors.end(), Red) - colors.begin();
            if (englishman != red) continue;

            for (const auto& pets : pet_perms) {
                // 3. The Spaniard owns the dog.
                int spaniard = std::find(nationalities.begin(), nationalities.end(), Spaniard) - nationalities.begin();
                int dog = std::find(pets.begin(), pets.end(), Dog) - pets.begin();
                if (spaniard != dog) continue;

                for (const auto& drinks : drink_perms) {
                    // 9. The person in the middle house drinks milk.
                    if (drinks[2] != Milk) continue;
                    // 4. The person in the green house drinks coffee.
                    if (drinks[green] != Coffee) continue;
                    // 5. The Ukrainian drinks tea.
                    int ukrainian = std::find(nationalities.begin(), nationalities.end(), Ukrainian) - nationalities.begin();
                    if (drinks[ukrainian] != Tea) continue;
                    // 13. The person who plays football drinks orange juice.
                    // (Handled in hobby loop)

                    for (const auto& hobbies : hobby_perms) {
                        // 8. The person in the yellow house is a painter.
                        int yellow = std::find(colors.begin(), colors.end(), Yellow) - colors.begin();
                        int painter = std::find(hobbies.begin(), hobbies.end(), Painting) - hobbies.begin();
                        if (yellow != painter) continue;
                        // 14. The Japanese person plays chess.
                        int japanese = std::find(nationalities.begin(), nationalities.end(), Japanese) - nationalities.begin();
                        int chess = std::find(hobbies.begin(), hobbies.end(), Chess) - hobbies.begin();
                        if (japanese != chess) continue;
                        // 13. The person who plays football drinks orange juice.
                        int football = std::find(hobbies.begin(), hobbies.end(), Football) - hobbies.begin();
                        if (drinks[football] != OrangeJuice) continue;
                        // 7. The snail owner likes to go dancing.
                        int snails = std::find(pets.begin(), pets.end(), Snails) - pets.begin();
                        int dancing = std::find(hobbies.begin(), hobbies.end(), Dancing) - hobbies.begin();
                        if (snails != dancing) continue;
                        // 11. The person who enjoys reading lives in the house next to the person with the fox.
                        int reading = std::find(hobbies.begin(), hobbies.end(), Reading) - hobbies.begin();
                        int fox = std::find(pets.begin(), pets.end(), Fox) - pets.begin();
                        if (!is_next_to(reading, fox)) continue;
                        // 12. The painter's house is next to the house with the horse.
                        int horse = std::find(pets.begin(), pets.end(), Horse) - pets.begin();
                        if (!is_next_to(painter, horse)) continue;

                        // All constraints satisfied, extract solution
                        int water = std::find(drinks.begin(), drinks.end(), Water) - drinks.begin();
                        int zebra = std::find(pets.begin(), pets.end(), Zebra) - pets.begin();
                        std::string drinksWater, ownsZebra;
                        switch (nationalities[water]) {
                            case Englishman: drinksWater = "Englishman"; break;
                            case Spaniard: drinksWater = "Spaniard"; break;
                            case Ukrainian: drinksWater = "Ukrainian"; break;
                            case Norwegian: drinksWater = "Norwegian"; break;
                            case Japanese: drinksWater = "Japanese"; break;
                        }
                        switch (nationalities[zebra]) {
                            case Englishman: ownsZebra = "Englishman"; break;
                            case Spaniard: ownsZebra = "Spaniard"; break;
                            case Ukrainian: ownsZebra = "Ukrainian"; break;
                            case Norwegian: ownsZebra = "Norwegian"; break;
                            case Japanese: ownsZebra = "Japanese"; break;
                        }
                        return Solution{drinksWater, ownsZebra};
                    }
                }
            }
        }
    }
    // Should never reach here for a well-formed puzzle
    return Solution{"", ""};
}

}  // namespace zebra_puzzle
