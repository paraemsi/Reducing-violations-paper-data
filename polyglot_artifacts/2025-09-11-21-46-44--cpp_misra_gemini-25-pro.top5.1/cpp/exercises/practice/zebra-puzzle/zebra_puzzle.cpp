#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cmath>
#include <string>

namespace zebra_puzzle {

enum class Color : std::uint8_t { Red, Green, Ivory, Yellow, Blue };
enum class Nationality : std::uint8_t {
    Englishman,
    Spaniard,
    Ukrainian,
    Norwegian,
    Japanese
};
enum class Pet : std::uint8_t { Dog, Snails, Fox, Horse, Zebra };
enum class Drink : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water };
enum class Hobby : std::uint8_t { Dancing, Painter, Reading, Football, Chess };

namespace {
std::string to_string(const Nationality nationality) {
    switch (nationality) {
    case Nationality::Englishman:
        return "Englishman";
    case Nationality::Spaniard:
        return "Spaniard";
    case Nationality::Ukrainian:
        return "Ukrainian";
    case Nationality::Norwegian:
        return "Norwegian";
    case Nationality::Japanese:
        return "Japanese";
    }
    return "";
}
} // namespace

Solution solve() {
    std::array<std::uint8_t, 5> p = {0, 1, 2, 3, 4};

    auto nationalities = p;
    auto colors = p;
    auto pets = p;
    auto drinks = p;
    auto hobbies = p;

    using N = Nationality;
    using C = Color;
    using P = Pet;
    using D = Drink;
    using H = Hobby;

    do { // drinks
        if ((drinks[static_cast<std::uint8_t>(D::Milk)] != 2)) {
            continue;
        }

        do { // nationalities
            if ((nationalities[static_cast<std::uint8_t>(N::Norwegian)] != 0)) {
                continue;
            }
            if ((nationalities[static_cast<std::uint8_t>(N::Ukrainian)] !=
                 drinks[static_cast<std::uint8_t>(D::Tea)])) {
                continue;
            }

            do { // colors
                if ((colors[static_cast<std::uint8_t>(C::Blue)] != 1)) {
                    continue;
                }
                if ((colors[static_cast<std::uint8_t>(C::Green)] !=
                     (colors[static_cast<std::uint8_t>(C::Ivory)] + 1))) {
                    continue;
                }
                if ((nationalities[static_cast<std::uint8_t>(N::Englishman)] !=
                     colors[static_cast<std::uint8_t>(C::Red)])) {
                    continue;
                }
                if ((colors[static_cast<std::uint8_t>(C::Green)] !=
                     drinks[static_cast<std::uint8_t>(D::Coffee)])) {
                    continue;
                }

                do { // hobbies
                    if ((colors[static_cast<std::uint8_t>(C::Yellow)] !=
                         hobbies[static_cast<std::uint8_t>(H::Painter)])) {
                        continue;
                    }
                    if ((hobbies[static_cast<std::uint8_t>(H::Football)] !=
                         drinks[static_cast<std::uint8_t>(D::OrangeJuice)])) {
                        continue;
                    }
                    if ((nationalities[static_cast<std::uint8_t>(N::Japanese)] !=
                         hobbies[static_cast<std::uint8_t>(H::Chess)])) {
                        continue;
                    }

                    do { // pets
                        if ((nationalities[static_cast<std::uint8_t>(N::Spaniard)] !=
                             pets[static_cast<std::uint8_t>(P::Dog)])) {
                            continue;
                        }
                        if ((pets[static_cast<std::uint8_t>(P::Snails)] !=
                             hobbies[static_cast<std::uint8_t>(H::Dancing)])) {
                            continue;
                        }
                        if ((std::abs(static_cast<std::int32_t>(
                                         hobbies[static_cast<std::uint8_t>(H::Reading)]) -
                                     static_cast<std::int32_t>(
                                         pets[static_cast<std::uint8_t>(P::Fox)])) != 1)) {
                            continue;
                        }
                        if ((std::abs(static_cast<std::int32_t>(
                                         hobbies[static_cast<std::uint8_t>(H::Painter)]) -
                                     static_cast<std::int32_t>(
                                         pets[static_cast<std::uint8_t>(P::Horse)])) != 1)) {
                            continue;
                        }

                        Solution solution;

                        const auto water_drinker_house =
                            drinks[static_cast<std::uint8_t>(D::Water)];
                        for (std::uint8_t i = 0; (i < 5); ++i) {
                            if ((nationalities[i] == water_drinker_house)) {
                                solution.drinksWater =
                                    to_string(static_cast<N>(i));
                                break;
                            }
                        }

                        const auto zebra_owner_house =
                            pets[static_cast<std::uint8_t>(P::Zebra)];
                        for (std::uint8_t i = 0; (i < 5); ++i) {
                            if ((nationalities[i] == zebra_owner_house)) {
                                solution.ownsZebra =
                                    to_string(static_cast<N>(i));
                                break;
                            }
                        }

                        return solution;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(colors.begin(), colors.end()));
        } while (
            std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(drinks.begin(), drinks.end()));

    return {};
}

} // namespace zebra_puzzle
