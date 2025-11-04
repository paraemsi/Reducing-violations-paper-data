#include "allergies.h"

#include <algorithm>
#include <array>

namespace allergies {

allergy_test::allergy_test(score_t score) noexcept
{
    /* List of all recognised allergens */
    static constexpr std::array<allergen, 8U> all_items{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const allergen item : all_items)
    {
        /* Check if the bit for this allergen is set in the score */
        if ((score & static_cast<score_t>(item)) != 0U)
        {
            (void)allergies_.emplace(item);   /* insert and explicitly discard bool return */
        }
    }
}

bool allergy_test::is_allergic_to(const allergen item) const noexcept
{
    return (allergies_.find(item) != allergies_.end());
}

std::vector<allergen> allergy_test::get_allergies() const
{
    std::vector<allergen> result{};
    result.reserve(allergies_.size());

    for (const allergen item : allergies_)
    {
        result.push_back(item);
    }

    /* Sort by underlying numeric value to give deterministic order */
    std::sort(result.begin(), result.end(), [](allergen a, allergen b)
    {
        return static_cast<std::uint8_t>(a) < static_cast<std::uint8_t>(b);
    });

    return result;
}

}  // namespace allergies
