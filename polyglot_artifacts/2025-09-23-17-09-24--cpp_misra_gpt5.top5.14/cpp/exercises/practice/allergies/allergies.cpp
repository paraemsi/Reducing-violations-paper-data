#include "allergies.h"

#include <array>

namespace allergies {

std::size_t allergen_hash::operator()(allergen a) const noexcept
{
    return static_cast<std::size_t>(static_cast<std::uint32_t>(a));
}

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score)
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    const std::uint32_t mask = static_cast<std::uint32_t>(item);
    const std::uint32_t filtered = (m_score & static_cast<std::uint32_t>(255U));
    return ((filtered & mask) != static_cast<std::uint32_t>(0));
}

allergen_set allergy_test::get_allergies() const
{
    static constexpr std::array<allergen, 8U> known{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    allergen_set result;
    result.reserve(static_cast<std::size_t>(known.size()));

    for (const allergen item : known) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

allergen_set allergy_test::list() const
{
    return get_allergies();
}

}  // namespace allergies
