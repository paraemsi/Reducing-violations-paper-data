#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace zebra_puzzle {

Solution solve()
{
    enum class Nationality : std::uint8_t { Englishman, Spaniard, Ukrainian, Norwegian, Japanese };
    enum class Colour      : std::uint8_t { Red, Green, Ivory, Yellow, Blue };
    enum class Pet         : std::uint8_t { Dog, Snail, Fox, Horse, Zebra };
    enum class Drink       : std::uint8_t { Coffee, Tea, Milk, OrangeJuice, Water };
    enum class Hobby       : std::uint8_t { Dancing, Painting, Reading, Football, Chess };

    /*  Helper to translate enum value back to a display name.  */
    const std::array<std::string_view, 5U> natNames {
        "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"
    };

    const std::array<std::uint8_t, 5U> base {
        static_cast<std::uint8_t>(0U), static_cast<std::uint8_t>(1U),
        static_cast<std::uint8_t>(2U), static_cast<std::uint8_t>(3U),
        static_cast<std::uint8_t>(4U)
    };

    auto position = [](const std::array<std::uint8_t, 5U>& arr,
                       std::uint8_t value) -> std::uint8_t
    {
        for (std::uint8_t idx { 0U }; idx < 5U; ++idx)
        {
            if (arr[static_cast<std::size_t>(idx)] == value)
            {
                return idx;
            }
        }
        return 5U;   /*  Should be unreachable.  */
    };

    Solution result {};

    std::array<std::uint8_t, 5U> colours = base;
    do
    {
        const std::uint8_t greenPos { position(colours,
                                               static_cast<std::uint8_t>(Colour::Green)) };
        const std::uint8_t ivoryPos { position(colours,
                                               static_cast<std::uint8_t>(Colour::Ivory)) };

        if (greenPos != (ivoryPos + 1U))
        {
            continue;
        }

        std::array<std::uint8_t, 5U> nationalities = base;
        do
        {
            if (nationalities[0U] != static_cast<std::uint8_t>(Nationality::Norwegian))
            {
                continue;
            }

            const std::uint8_t redPos { position(colours,
                                                 static_cast<std::uint8_t>(Colour::Red)) };
            if (nationalities[redPos] != static_cast<std::uint8_t>(Nationality::Englishman))
            {
                continue;
            }

            const std::uint8_t bluePos { position(colours,
                                                  static_cast<std::uint8_t>(Colour::Blue)) };
            const std::uint8_t norPos  { position(nationalities,
                                                  static_cast<std::uint8_t>(Nationality::Norwegian)) };

            if (((bluePos > norPos) ? (bluePos - norPos) : (norPos - bluePos)) != 1U)
            {
                continue;
            }

            std::array<std::uint8_t, 5U> drinks = base;
            do
            {
                if (drinks[2U] != static_cast<std::uint8_t>(Drink::Milk))
                {
                    continue;
                }

                if (drinks[position(colours,
                                    static_cast<std::uint8_t>(Colour::Green))] !=
                    static_cast<std::uint8_t>(Drink::Coffee))
                {
                    continue;
                }

                if (drinks[position(nationalities,
                                    static_cast<std::uint8_t>(Nationality::Ukrainian))] !=
                    static_cast<std::uint8_t>(Drink::Tea))
                {
                    continue;
                }

                std::array<std::uint8_t, 5U> pets = base;
                do
                {
                    if (pets[position(nationalities,
                                      static_cast<std::uint8_t>(Nationality::Spaniard))] !=
                        static_cast<std::uint8_t>(Pet::Dog))
                    {
                        continue;
                    }

                    std::array<std::uint8_t, 5U> hobbies = base;
                    do
                    {
                        if (hobbies[position(pets,
                                             static_cast<std::uint8_t>(Pet::Snail))] !=
                            static_cast<std::uint8_t>(Hobby::Dancing))
                        {
                            continue;
                        }

                        if (hobbies[position(colours,
                                             static_cast<std::uint8_t>(Colour::Yellow))] !=
                            static_cast<std::uint8_t>(Hobby::Painting))
                        {
                            continue;
                        }

                        if (hobbies[position(nationalities,
                                             static_cast<std::uint8_t>(Nationality::Japanese))] !=
                            static_cast<std::uint8_t>(Hobby::Chess))
                        {
                            continue;
                        }

                        if (drinks[position(hobbies,
                                            static_cast<std::uint8_t>(Hobby::Football))] !=
                            static_cast<std::uint8_t>(Drink::OrangeJuice))
                        {
                            continue;
                        }

                        const std::uint8_t readerPos { position(hobbies,
                                                                static_cast<std::uint8_t>(Hobby::Reading)) };
                        const std::uint8_t foxPos    { position(pets,
                                                                static_cast<std::uint8_t>(Pet::Fox)) };

                        if (((readerPos > foxPos) ? (readerPos - foxPos) : (foxPos - readerPos)) != 1U)
                        {
                            continue;
                        }

                        const std::uint8_t painterPos { position(hobbies,
                                                                 static_cast<std::uint8_t>(Hobby::Painting)) };
                        const std::uint8_t horsePos   { position(pets,
                                                                 static_cast<std::uint8_t>(Pet::Horse)) };

                        if (((painterPos > horsePos) ? (painterPos - horsePos) : (horsePos - painterPos)) != 1U)
                        {
                            continue;
                        }

                        const std::uint8_t waterPos { position(drinks,
                                                               static_cast<std::uint8_t>(Drink::Water)) };
                        const std::uint8_t zebraPos { position(pets,
                                                               static_cast<std::uint8_t>(Pet::Zebra)) };

                        result.drinksWater =
                            std::string(natNames[static_cast<std::size_t>(nationalities[waterPos])]);
                        result.ownsZebra =
                            std::string(natNames[static_cast<std::size_t>(nationalities[zebraPos])]);

                        return result;

                    } while (std::next_permutation(hobbies.begin(), hobbies.end()));

                } while (std::next_permutation(pets.begin(), pets.end()));

            } while (std::next_permutation(drinks.begin(), drinks.end()));

        } while (std::next_permutation(nationalities.begin(), nationalities.end()));

    } while (std::next_permutation(colours.begin(), colours.end()));

    return result;   /*  Fallback – puzzle guarantees a unique solution.  */
}

}   /* namespace zebra_puzzle */
