#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>

namespace zebra_puzzle {

namespace {
    enum class Color : std::size_t { Red = 0U, Green = 1U, Ivory = 2U, Yellow = 3U, Blue = 4U };
    enum class Nationality : std::size_t { English = 0U, Spaniard = 1U, Ukrainian = 2U, Norwegian = 3U, Japanese = 4U };
    enum class Drink : std::size_t { Coffee = 0U, Tea = 1U, Milk = 2U, OrangeJuice = 3U, Water = 4U };
    enum class Pet : std::size_t { Dog = 0U, Fox = 1U, Horse = 2U, Snails = 3U, Zebra = 4U };
    enum class Hobby : std::size_t { Dancing = 0U, Painter = 1U, Reading = 2U, Football = 3U, Chess = 4U };

    using Positions = std::array<std::size_t, 5U>;

    inline std::size_t abs_diff(std::size_t a, std::size_t b) {
        return (a > b) ? (a - b) : (b - a);
    }

    inline std::size_t find_index_at_pos(const Positions& arr, std::size_t pos) {
        for (std::size_t i = 0U; i < static_cast<std::size_t>(arr.size()); i++) {
            if ((arr[i] == pos)) {
                return i;
            }
        }
        return static_cast<std::size_t>(arr.size());
    }

    inline bool colors_ok(const Positions& color) {
        const std::size_t blue = color[static_cast<std::size_t>(Color::Blue)];
        const std::size_t green = color[static_cast<std::size_t>(Color::Green)];
        const std::size_t ivory = color[static_cast<std::size_t>(Color::Ivory)];

        if ((blue != 1U)) {
            return false;
        }
        if ((green != (ivory + 1U))) {
            return false;
        }
        return true;
    }

    inline bool nat_color_basic_ok(const Positions& nat, const Positions& color) {
        // Englishman lives in the red house.
        if ((nat[static_cast<std::size_t>(Nationality::English)] != color[static_cast<std::size_t>(Color::Red)])) {
            return false;
        }
        // Norwegian lives in the first house.
        if ((nat[static_cast<std::size_t>(Nationality::Norwegian)] != 0U)) {
            return false;
        }
        // Norwegian lives next to the blue house.
        if ((abs_diff(
                nat[static_cast<std::size_t>(Nationality::Norwegian)],
                color[static_cast<std::size_t>(Color::Blue)]) != 1U)) {
            return false;
        }
        return true;
    }

    inline bool drinks_ok(const Positions& drinks, const Positions& color, const Positions& nat) {
        // Middle house drinks milk.
        if ((drinks[static_cast<std::size_t>(Drink::Milk)] != 2U)) {
            return false;
        }
        // Green house drinks coffee.
        if ((color[static_cast<std::size_t>(Color::Green)] != drinks[static_cast<std::size_t>(Drink::Coffee)])) {
            return false;
        }
        // Ukrainian drinks tea.
        if ((nat[static_cast<std::size_t>(Nationality::Ukrainian)] != drinks[static_cast<std::size_t>(Drink::Tea)])) {
            return false;
        }
        return true;
    }

    inline bool pets_ok(const Positions& pets, const Positions& nat) {
        // Spaniard owns the dog.
        if ((nat[static_cast<std::size_t>(Nationality::Spaniard)] != pets[static_cast<std::size_t>(Pet::Dog)])) {
            return false;
        }
        return true;
    }

    inline bool hobbies_ok(
        const Positions& hobbies,
        const Positions& pets,
        const Positions& color,
        const Positions& drinks,
        const Positions& nat) {
        // Snail owner likes to go dancing.
        if ((pets[static_cast<std::size_t>(Pet::Snails)] != hobbies[static_cast<std::size_t>(Hobby::Dancing)])) {
            return false;
        }
        // Yellow house is a painter.
        if ((color[static_cast<std::size_t>(Color::Yellow)] != hobbies[static_cast<std::size_t>(Hobby::Painter)])) {
            return false;
        }
        // Football player drinks orange juice.
        if ((hobbies[static_cast<std::size_t>(Hobby::Football)] != drinks[static_cast<std::size_t>(Drink::OrangeJuice)])) {
            return false;
        }
        // Japanese person plays chess.
        if ((nat[static_cast<std::size_t>(Nationality::Japanese)] != hobbies[static_cast<std::size_t>(Hobby::Chess)])) {
            return false;
        }
        // Reader lives next to fox.
        if ((abs_diff(
                hobbies[static_cast<std::size_t>(Hobby::Reading)],
                pets[static_cast<std::size_t>(Pet::Fox)]) != 1U)) {
            return false;
        }
        // Painter's house is next to the house with the horse.
        if ((abs_diff(
                hobbies[static_cast<std::size_t>(Hobby::Painter)],
                pets[static_cast<std::size_t>(Pet::Horse)]) != 1U)) {
            return false;
        }
        return true;
    }
}  // namespace

Solution solve() {
    const Positions base{ { 0U, 1U, 2U, 3U, 4U } };

    const std::array<std::string, 5U> natNames{
        { "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese" }
    };

    Positions color = base;
    do {
        if ((!colors_ok(color))) {
            continue;
        }

        Positions nat = base;
        do {
            // Norwegian must be in first house
            if ((nat[static_cast<std::size_t>(Nationality::Norwegian)] != 0U)) {
                continue;
            }
            if ((!nat_color_basic_ok(nat, color))) {
                continue;
            }

            Positions drinks = base;
            do {
                if ((!drinks_ok(drinks, color, nat))) {
                    continue;
                }

                Positions pets = base;
                do {
                    if ((!pets_ok(pets, nat))) {
                        continue;
                    }

                    Positions hobbies = base;
                    do {
                        if ((!hobbies_ok(hobbies, pets, color, drinks, nat))) {
                            continue;
                        }

                        // All constraints satisfied; compute solution.
                        const std::size_t waterPos = drinks[static_cast<std::size_t>(Drink::Water)];
                        const std::size_t zebraPos = pets[static_cast<std::size_t>(Pet::Zebra)];

                        const std::size_t whoDrinksWater =
                            find_index_at_pos(nat, waterPos);
                        const std::size_t whoOwnsZebra =
                            find_index_at_pos(nat, zebraPos);

                        Solution sol{};
                        if ((whoDrinksWater < natNames.size())) {
                            sol.drinksWater = natNames[whoDrinksWater];
                        }
                        if ((whoOwnsZebra < natNames.size())) {
                            sol.ownsZebra = natNames[whoOwnsZebra];
                        }
                        return sol;
                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));
                } while (std::next_permutation(pets.begin(), pets.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nat.begin(), nat.end()));
    } while (std::next_permutation(color.begin(), color.end()));

    // Fallback (should not happen for a well-posed puzzle)
    Solution sol{};
    sol.drinksWater = "";
    sol.ownsZebra = "";
    return sol;
}

}  // namespace zebra_puzzle
