#include "allergies.h"
#include <unordered_set>

namespace allergies {

constexpr std::array<allergen, 8U> allergy_test::known_allergens{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};

allergy_test::allergy_test(const std::uint32_t score_in) noexcept
    : score{score_in}
{
    /* No further initialisation required */
}

bool allergy_test::is_allergic_to(const allergen item) const noexcept
{
    return ((score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result{};

    for (const allergen al : allergy_test::known_allergens)
    {
        if (is_allergic_to(al))
        {
            result.emplace(al);
        }
    }

    return result;
}

}  // namespace allergies
