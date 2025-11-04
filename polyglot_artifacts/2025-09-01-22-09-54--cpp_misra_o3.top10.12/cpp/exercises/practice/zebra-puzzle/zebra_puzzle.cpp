#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

constexpr std::uint32_t HOUSE_COUNT = 5U;

enum class Color : std::uint32_t {
    RED = 0U,
    GREEN = 1U,
    IVORY = 2U,
    YELLOW = 3U,
    BLUE = 4U
};

enum class Nationality : std::uint32_t {
    ENGLISH = 0U,
    SPANISH = 1U,
    UKRAINIAN = 2U,
    NORWEGIAN = 3U,
    JAPANESE = 4U
};

enum class Pet : std::uint32_t {
    DOG = 0U,
    SNAILS = 1U,
    FOX = 2U,
    HORSE = 3U,
    ZEBRA = 4U
};

enum class Drink : std::uint32_t {
    COFFEE = 0U,
    TEA = 1U,
    MILK = 2U,
    ORANGE_JUICE = 3U,
    WATER = 4U
};

enum class Hobby : std::uint32_t {
    DANCING = 0U,
    PAINTING = 1U,
    READING = 2U,
    FOOTBALL = 3U,
    CHESS = 4U
};

template <typename T>
using Positions = std::array<std::uint32_t, HOUSE_COUNT>;

template <typename T>
[[nodiscard]] constexpr auto as_index(const T value) -> std::uint32_t
{
    return static_cast<std::uint32_t>(value);
}

[[nodiscard]] auto base_permutation() -> Positions<std::uint32_t>
{
    Positions<std::uint32_t> perm{{0U, 1U, 2U, 3U, 4U}};
    return perm;
}

}  // unnamed namespace

auto solve() -> Solution
{
    Positions<std::uint32_t> color{};
    Positions<std::uint32_t> nat{};
    Positions<std::uint32_t> pet{};
    Positions<std::uint32_t> drink{};
    Positions<std::uint32_t> hobby{};

    Positions<std::uint32_t> perm = base_permutation();

    do
    {
        color = perm;

        /* Constraint 6: green is immediately right of ivory */
        if((color[as_index(Color::GREEN)] != (color[as_index(Color::IVORY)] + 1U)))
        {
            continue;
        }

        /* Generate nationality permutations */
        Positions<std::uint32_t> natPerm = base_permutation();
        do
        {
            nat = natPerm;

            /* Constraint 10: Norwegian lives in first house */
            if(nat[as_index(Nationality::NORWEGIAN)] != 0U)
            {
                continue;
            }

            /* Constraint 2: Englishman lives in the red house */
            if(nat[as_index(Nationality::ENGLISH)] != color[as_index(Color::RED)])
            {
                continue;
            }

            /* Constraint 15: Norwegian lives next to blue house */
            bool norwegian_left_of_blue  = false;
            bool norwegian_right_of_blue = false;
            if(nat[as_index(Nationality::NORWEGIAN)] > 0U)
            {
                norwegian_left_of_blue =
                    ((nat[as_index(Nationality::NORWEGIAN)] - 1U) == color[as_index(Color::BLUE)]);
            }
            norwegian_right_of_blue =
                ((nat[as_index(Nationality::NORWEGIAN)] + 1U) == color[as_index(Color::BLUE)]);

            if(!(norwegian_left_of_blue || norwegian_right_of_blue))
            {
                continue;
            }

            /* Drinks permutation */
            Positions<std::uint32_t> drinkPerm = base_permutation();
            do
            {
                drink = drinkPerm;

                /* Constraint 4: green house drinks coffee */
                if(drink[as_index(Drink::COFFEE)] != color[as_index(Color::GREEN)])
                {
                    continue;
                }

                /* Constraint 5: Ukrainian drinks tea */
                if(drink[as_index(Drink::TEA)] != nat[as_index(Nationality::UKRAINIAN)])
                {
                    continue;
                }

                /* Constraint 9: middle house drinks milk */
                if(drink[as_index(Drink::MILK)] != 2U)
                {
                    continue;
                }

                /* Pet permutation */
                Positions<std::uint32_t> petPerm = base_permutation();
                do
                {
                    pet = petPerm;

                    /* Constraint 3: Spaniard owns the dog */
                    if(pet[as_index(Pet::DOG)] != nat[as_index(Nationality::SPANISH)])
                    {
                        continue;
                    }

                    /* Hobby permutation */
                    Positions<std::uint32_t> hobbyPerm = base_permutation();
                    do
                    {
                        hobby = hobbyPerm;

                        /* Constraint 7: Snail owner likes dancing */
                        if(hobby[as_index(Hobby::DANCING)] != pet[as_index(Pet::SNAILS)])
                        {
                            continue;
                        }

                        /* Constraint 8: Yellow house's resident is a painter */
                        if(hobby[as_index(Hobby::PAINTING)] != color[as_index(Color::YELLOW)])
                        {
                            continue;
                        }

                        /* Constraint 13: Football player drinks orange juice */
                        if(hobby[as_index(Hobby::FOOTBALL)] != drink[as_index(Drink::ORANGE_JUICE)])
                        {
                            continue;
                        }

                        /* Constraint 14: Japanese person plays chess */
                        if(hobby[as_index(Hobby::CHESS)] != nat[as_index(Nationality::JAPANESE)])
                        {
                            continue;
                        }

                        /* Constraint 11: Reading hobby lives next to fox owner */
                        bool reading_left_of_fox  = false;
                        bool reading_right_of_fox = false;
                        if(hobby[as_index(Hobby::READING)] > 0U)
                        {
                            reading_left_of_fox =
                                ((hobby[as_index(Hobby::READING)] - 1U) == pet[as_index(Pet::FOX)]);
                        }
                        reading_right_of_fox =
                            ((hobby[as_index(Hobby::READING)] + 1U) == pet[as_index(Pet::FOX)]);

                        if(!(reading_left_of_fox || reading_right_of_fox))
                        {
                            continue;
                        }

                        /* Constraint 12: Painter lives next to horse owner */
                        bool painter_left_of_horse  = false;
                        bool painter_right_of_horse = false;
                        if(hobby[as_index(Hobby::PAINTING)] > 0U)
                        {
                            painter_left_of_horse =
                                ((hobby[as_index(Hobby::PAINTING)] - 1U) == pet[as_index(Pet::HORSE)]);
                        }
                        painter_right_of_horse =
                            ((hobby[as_index(Hobby::PAINTING)] + 1U) == pet[as_index(Pet::HORSE)]);

                        if(!(painter_left_of_horse || painter_right_of_horse))
                        {
                            continue;
                        }

                        /* All constraints satisfied — build the answer */
                        Solution solution{};

                        static const std::array<std::string, HOUSE_COUNT> NATIONALITY_NAMES{
                            "Englishman", "Spaniard", "Ukrainian", "Norwegian", "Japanese"};

                        for(std::uint32_t idx = 0U; idx < HOUSE_COUNT; ++idx)
                        {
                            if(nat[idx] == drink[as_index(Drink::WATER)])
                            {
                                solution.drinksWater = NATIONALITY_NAMES[idx];
                            }
                            if(nat[idx] == pet[as_index(Pet::ZEBRA)])
                            {
                                solution.ownsZebra = NATIONALITY_NAMES[idx];
                            }
                        }

                        return solution;

                    } while(std::next_permutation(hobbyPerm.begin(), hobbyPerm.end()));
                } while(std::next_permutation(petPerm.begin(), petPerm.end()));
            } while(std::next_permutation(drinkPerm.begin(), drinkPerm.end()));
        } while(std::next_permutation(natPerm.begin(), natPerm.end()));
    } while(std::next_permutation(perm.begin(), perm.end()));

    /* Should never be reached */
    return Solution{};
}

}  // namespace zebra_puzzle
