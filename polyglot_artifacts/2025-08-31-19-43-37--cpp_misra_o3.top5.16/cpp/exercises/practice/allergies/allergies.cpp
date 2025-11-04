#include "allergies.h"

#include <cstddef>
#include <functional>

namespace std {

template<>
struct hash<allergies::allergen>
{
    std::size_t operator()(const allergies::allergen& a) const noexcept
    {
        return std::hash<std::uint16_t>{}(static_cast<std::uint16_t>(a));
    }
};

}  // namespace std

namespace allergies {

allergy_test::allergy_test(std::uint16_t score) noexcept
    : m_score(score)
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((m_score & static_cast<std::uint16_t>(item)) != 0U);
}

std::unordered_set<allergen> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<allergen> result {};

    for (auto a : { allergen::eggs,
                    allergen::peanuts,
                    allergen::shellfish,
                    allergen::strawberries,
                    allergen::tomatoes,
                    allergen::chocolate,
                    allergen::pollen,
                    allergen::cats })
    {
        if (is_allergic_to(a)) {
            (void)result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies

