#include "allergies.h"

#include <array>

namespace allergies {

namespace {
    constexpr std::array<allergen, 8U> all_allergens = {
        allergen::eggs, allergen::peanuts, allergen::shellfish, allergen::strawberries,
        allergen::tomatoes, allergen::chocolate, allergen::pollen, allergen::cats
    };

    /* 8-bit mask – only the lowest 8 bits of the supplied score are relevant */
    constexpr std::uint32_t valid_mask = static_cast<std::uint32_t>(255U);
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : score{ (score_in & valid_mask) } { }

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0U));
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result {};
    for (auto const current : all_allergens) {
        if (is_allergic_to(current)) {
            (void)result.emplace(current);
        }
    }
    return result;
}

}  // namespace allergies
