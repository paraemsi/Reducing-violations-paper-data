#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : score(score_in) { }

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    auto mask = static_cast<std::uint32_t>(item);
    return ((score & mask) != 0u);
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
    std::unordered_set<allergen> result {};

    for (auto item : { allergen::eggs, allergen::peanuts, allergen::shellfish,
                       allergen::strawberries, allergen::tomatoes,
                       allergen::chocolate, allergen::pollen,
                       allergen::cats }) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies
