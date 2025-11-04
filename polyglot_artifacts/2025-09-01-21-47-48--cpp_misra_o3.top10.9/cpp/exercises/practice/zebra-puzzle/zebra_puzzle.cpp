#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle
{

namespace
{

template <typename T, std::size_t N, typename U>
[[nodiscard]] constexpr auto index_of(const std::array<T, N>& arr, U value) -> std::int32_t
{
    const T target = static_cast<T>(value); /* Intentional cast: enum → underlying */
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(N); ++i)
    {
        if (arr[static_cast<std::size_t>(i)] == target)
        {
            return i;
        }
    }
    return -1; /* Unreachable if used correctly */
}

} // unnamed namespace

auto solve() -> Solution
{
    enum Color : std::int32_t
    {
        kRed = 0,
        kGreen,
        kIvory,
        kYellow,
        kBlue
    };
    enum Nationality : std::int32_t
    {
        kEnglishman = 0,
        kSpaniard,
        kUkrainian,
        kNorwegian,
        kJapanese
    };
    enum Pet : std::int32_t
    {
        kDog = 0,
        kSnails,
        kFox,
        kHorse,
        kZebra
    };
    enum Drink : std::int32_t
    {
        kCoffee = 0,
        kTea,
        kMilk,
        kOrangeJuice,
        kWater
    };
    enum Hobby : std::int32_t
    {
        kReading = 0,
        kChess,
        kDancing,
        kPainting,
        kFootball
    };

    /* Initial permutation seed */
    const std::array<std::int32_t, 5> seed{{0, 1, 2, 3, 4}};

    std::array<std::int32_t, 5> colors{};
    std::array<std::int32_t, 5> nationalities{};
    std::array<std::int32_t, 5> drinks{};
    std::array<std::int32_t, 5> hobbies{};
    std::array<std::int32_t, 5> pets{};

    colors = seed;
    do
    {
        const std::int32_t idxGreen  = index_of(colors, kGreen);
        const std::int32_t idxIvory  = index_of(colors, kIvory);

        /* #6 The green house is immediately to the right of the ivory house. */
        if (idxGreen != (idxIvory + 1))
        {
            continue;
        }

        nationalities = seed;
        do
        {
            /* #2 The Englishman lives in the red house. */
            const std::int32_t idxEnglish   = index_of(nationalities, kEnglishman);
            if (colors[static_cast<std::size_t>(idxEnglish)] != kRed)
            {
                continue;
            }

            /* #10 The Norwegian lives in the first house. */
            const std::int32_t idxNorwegian = index_of(nationalities, kNorwegian);
            if (idxNorwegian != 0)
            {
                continue;
            }

            /* #15 The Norwegian lives next to the blue house. */
            const std::int32_t idxBlue = index_of(colors, kBlue);
            if ((idxNorwegian != (idxBlue - 1)) && (idxNorwegian != (idxBlue + 1)))
            {
                continue;
            }

            drinks = seed;
            do
            {
                /* #4 The person in the green house drinks coffee. */
                if (drinks[static_cast<std::size_t>(idxGreen)] != kCoffee)
                {
                    continue;
                }

                /* #5 The Ukrainian drinks tea. */
                const std::int32_t idxUkrainian = index_of(nationalities, kUkrainian);
                if (drinks[static_cast<std::size_t>(idxUkrainian)] != kTea)
                {
                    continue;
                }

                /* #9 The person in the middle house drinks milk. */
                if (drinks[2] != kMilk)
                {
                    continue;
                }

                hobbies = seed;
                do
                {
                    /* #8 The person in the yellow house is a painter. */
                    const std::int32_t idxPainter = index_of(hobbies, kPainting);
                    if (colors[static_cast<std::size_t>(idxPainter)] != kYellow)
                    {
                        continue;
                    }

                    /* #14 The Japanese person plays chess. */
                    const std::int32_t idxJapanese = index_of(nationalities, kJapanese);
                    if (hobbies[static_cast<std::size_t>(idxJapanese)] != kChess)
                    {
                        continue;
                    }

                    /* #13 The person who plays football drinks orange juice. */
                    const std::int32_t idxFootball = index_of(hobbies, kFootball);
                    if (drinks[static_cast<std::size_t>(idxFootball)] != kOrangeJuice)
                    {
                        continue;
                    }

                    pets = seed;
                    do
                    {
                        /* #3 The Spaniard owns the dog. */
                        const std::int32_t idxSpaniard = index_of(nationalities, kSpaniard);
                        if (pets[static_cast<std::size_t>(idxSpaniard)] != kDog)
                        {
                            continue;
                        }

                        /* #7 The snail owner likes to go dancing. */
                        const std::int32_t idxSnails = index_of(pets, kSnails);
                        if (hobbies[static_cast<std::size_t>(idxSnails)] != kDancing)
                        {
                            continue;
                        }

                        /* #11 Reading lives next to the fox owner. */
                        const std::int32_t idxReading = index_of(hobbies, kReading);
                        const std::int32_t idxFox     = index_of(pets, kFox);
                        if ((idxReading != (idxFox - 1)) && (idxReading != (idxFox + 1)))
                        {
                            continue;
                        }

                        /* #12 The painter's house is next to the house with the horse. */
                        const std::int32_t idxHorse = index_of(pets, kHorse);
                        if ((idxPainter != (idxHorse - 1)) && (idxPainter != (idxHorse + 1)))
                        {
                            continue;
                        }

                        /* All constraints satisfied – build the answer. */
                        const std::string drinksWater = [&]() -> std::string
                        {
                            const std::int32_t idxWater = index_of(drinks, kWater);
                            const std::int32_t nat      = nationalities[static_cast<std::size_t>(idxWater)];
                            switch (nat)
                            {
                                case kEnglishman: return "Englishman";
                                case kSpaniard:   return "Spaniard";
                                case kUkrainian:  return "Ukrainian";
                                case kNorwegian:  return "Norwegian";
                                case kJapanese:   return "Japanese";
                                default:          return "";
                            }
                        }();

                        const std::string ownsZebra = [&]() -> std::string
                        {
                            const std::int32_t idxZebra = index_of(pets, kZebra);
                            const std::int32_t nat      = nationalities[static_cast<std::size_t>(idxZebra)];
                            switch (nat)
                            {
                                case kEnglishman: return "Englishman";
                                case kSpaniard:   return "Spaniard";
                                case kUkrainian:  return "Ukrainian";
                                case kNorwegian:  return "Norwegian";
                                case kJapanese:   return "Japanese";
                                default:          return "";
                            }
                        }();

                        Solution result{drinksWater, ownsZebra};
                        return result;

                    } while (std::next_permutation(pets.begin(), pets.end()));
                } while (std::next_permutation(hobbies.begin(), hobbies.end()));
            } while (std::next_permutation(drinks.begin(), drinks.end()));
        } while (std::next_permutation(nationalities.begin(), nationalities.end()));
    } while (std::next_permutation(colors.begin(), colors.end()));

    /* Should never reach this point */
    return Solution{"", ""};
}

} // namespace zebra_puzzle
