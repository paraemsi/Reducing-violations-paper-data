#include "zebra_puzzle.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

namespace zebra_puzzle {

namespace {

constexpr std::size_t kHouseCount{5U};

enum class Color : std::int32_t { red, green, ivory, yellow, blue };
enum class Nationality : std::int32_t { english, spaniard, ukrainian, norwegian, japanese };
enum class Pet : std::int32_t { dog, snails, fox, horse, zebra };
enum class Drink : std::int32_t { coffee, tea, milk, orange_juice, water };
enum class Hobby : std::int32_t { dancing, painting, reading, football, chess };

template <typename T>
constexpr std::size_t index_of(const std::array<T, kHouseCount>& houses, T value)
{
    for (std::size_t i{0U}; i < kHouseCount; ++i) {
        if (houses[i] == value) {
            return i;
        }
    }
    return kHouseCount;
}

} // unnamed namespace

Solution solve()
{
    std::array<std::int32_t, kHouseCount> base{{0, 1, 2, 3, 4}};

    std::array<Color, kHouseCount> colors{};
    std::array<Nationality, kHouseCount> nationalities{};
    std::array<Pet, kHouseCount> pets{};
    std::array<Drink, kHouseCount> drinks{};
    std::array<Hobby, kHouseCount> hobbies{};

    std::array<std::int32_t, kHouseCount> perm_colors = base;
    do {
        for (std::size_t i{0U}; i < kHouseCount; ++i) {
            colors[i] = static_cast<Color>(perm_colors[i]);
        }

        const std::size_t idx_green{index_of(colors, Color::green)};
        const std::size_t idx_ivory{index_of(colors, Color::ivory)};
        if ((idx_green != (idx_ivory + 1U))) {
            continue;
        }

        std::array<std::int32_t, kHouseCount> perm_nat = base;
        do {
            for (std::size_t i{0U}; i < kHouseCount; ++i) {
                nationalities[i] = static_cast<Nationality>(perm_nat[i]);
            }

            if (nationalities[0] != Nationality::norwegian) {
                continue;
            }

            if (colors[index_of(nationalities, Nationality::english)] != Color::red) {
                continue;
            }

            const std::size_t idx_norwegian{0U};
            bool norwegian_next_to_blue{false};
            if (idx_norwegian > 0U) {
                norwegian_next_to_blue = (colors[idx_norwegian - 1U] == Color::blue);
            }
            if (!norwegian_next_to_blue && (idx_norwegian + 1U < kHouseCount)) {
                norwegian_next_to_blue = (colors[idx_norwegian + 1U] == Color::blue);
            }
            if (!norwegian_next_to_blue) {
                continue;
            }

            std::array<std::int32_t, kHouseCount> perm_pet = base;
            do {
                for (std::size_t i{0U}; i < kHouseCount; ++i) {
                    pets[i] = static_cast<Pet>(perm_pet[i]);
                }

                if (pets[index_of(nationalities, Nationality::spaniard)] != Pet::dog) {
                    continue;
                }

                std::array<std::int32_t, kHouseCount> perm_drink = base;
                do {
                    for (std::size_t i{0U}; i < kHouseCount; ++i) {
                        drinks[i] = static_cast<Drink>(perm_drink[i]);
                    }

                    if (drinks[2] != Drink::milk) {
                        continue;
                    }

                    if (drinks[idx_green] != Drink::coffee) {
                        continue;
                    }

                    if (drinks[index_of(nationalities, Nationality::ukrainian)] != Drink::tea) {
                        continue;
                    }

                    std::array<std::int32_t, kHouseCount> perm_hobby = base;
                    do {
                        for (std::size_t i{0U}; i < kHouseCount; ++i) {
                            hobbies[i] = static_cast<Hobby>(perm_hobby[i]);
                        }

                        if (hobbies[index_of(pets, Pet::snails)] != Hobby::dancing) {
                            continue;
                        }

                        if (hobbies[index_of(colors, Color::yellow)] != Hobby::painting) {
                            continue;
                        }

                        const std::size_t idx_reading{index_of(hobbies, Hobby::reading)};
                        const std::size_t idx_fox{index_of(pets, Pet::fox)};
                        if (!(((idx_reading > 0U) && ((idx_reading - 1U) == idx_fox)) ||
                              ((idx_reading + 1U < kHouseCount) && ((idx_reading + 1U) == idx_fox)))) {
                            continue;
                        }

                        const std::size_t idx_painter{index_of(hobbies, Hobby::painting)};
                        const std::size_t idx_horse{index_of(pets, Pet::horse)};
                        if (!(((idx_painter > 0U) && ((idx_painter - 1U) == idx_horse)) ||
                              ((idx_painter + 1U < kHouseCount) && ((idx_painter + 1U) == idx_horse)))) {
                            continue;
                        }

                        if (drinks[index_of(hobbies, Hobby::football)] != Drink::orange_juice) {
                            continue;
                        }

                        if (hobbies[index_of(nationalities, Nationality::japanese)] != Hobby::chess) {
                            continue;
                        }

                        Solution sol{};
                        const std::size_t idx_water{index_of(drinks, Drink::water)};
                        const std::size_t idx_zebra{index_of(pets, Pet::zebra)};

                        auto nat_to_string = [](Nationality nat) -> std::string {
                            switch (nat) {
                                case Nationality::english:   return "Englishman";
                                case Nationality::spaniard:  return "Spaniard";
                                case Nationality::ukrainian: return "Ukrainian";
                                case Nationality::norwegian: return "Norwegian";
                                case Nationality::japanese:  return "Japanese";
                                default:                     return "";
                            }
                        };

                        sol.drinksWater = nat_to_string(nationalities[idx_water]);
                        sol.ownsZebra   = nat_to_string(nationalities[idx_zebra]);
                        return sol;

                    } while (std::next_permutation(perm_hobby.begin(), perm_hobby.end()));

                } while (std::next_permutation(perm_drink.begin(), perm_drink.end()));

            } while (std::next_permutation(perm_pet.begin(), perm_pet.end()));

        } while (std::next_permutation(perm_nat.begin(), perm_nat.end()));

    } while (std::next_permutation(perm_colors.begin(), perm_colors.end()));

    return Solution{};
}

} // namespace zebra_puzzle
