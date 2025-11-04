#include "allergies.h"
#include <array>

namespace allergies {


allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score}
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    const std::uint32_t mask = static_cast<std::uint32_t>(static_cast<std::uint16_t>(item));
    return ((score_ & mask) != static_cast<std::uint32_t>(0U));
}

allergen_set allergy_test::get_allergies() const
{
    static constexpr std::array<allergen, 8U> all_items = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    allergen_set result{};

    for (auto const item : all_items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies
