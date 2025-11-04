#include "allergies.h"

namespace allergies {

/* Constructor storing the provided score */
allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score)
{
}

/* Check whether the given allergen bit is set in the score */
bool allergy_test::is_allergic_to(allergen a) const noexcept
{
    return ( (m_score & static_cast<std::uint32_t>(a)) != 0u );
}

/* Build the complete set of allergens present in the score */
std::unordered_set<allergen> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<allergen> result {};

    for (const auto& item : { allergen::eggs, allergen::peanuts, allergen::shellfish,
                              allergen::strawberries, allergen::tomatoes, allergen::chocolate,
                              allergen::pollen, allergen::cats })
    {
        if ( (m_score & static_cast<std::uint32_t>(item)) != 0u )
        {
            (void)result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies
