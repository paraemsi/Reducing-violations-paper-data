#include "allergies.h"

#include <functional>   // std::hash for enum
#include <initializer_list>

namespace std {
template<>
struct hash<allergies::allergen>
{
    std::size_t operator()(const allergies::allergen& a) const noexcept
    {
        return static_cast<std::size_t>(a);
    }
};
} // namespace std

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score)
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((m_score & static_cast<std::uint32_t>(item)) != 0U);
}

std::unordered_set<allergen> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<allergen> result;

    const std::initializer_list<allergen> all_items{
        allergen::eggs, allergen::peanuts,   allergen::shellfish,
        allergen::strawberries, allergen::tomatoes, allergen::chocolate,
        allergen::pollen, allergen::cats};

    for (const allergen item : all_items)
    {
        if (is_allergic_to(item))
        {
            (void)result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies
