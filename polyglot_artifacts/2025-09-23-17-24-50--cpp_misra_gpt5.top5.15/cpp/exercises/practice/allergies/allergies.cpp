#include "allergies.h"

#include <array>

namespace allergies {

namespace {
constexpr std::array<allergen, 8U> kAllergens{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
};

constexpr std::uint32_t mask_for(allergen item) noexcept
{
    // Underlying enum type is std::uint16_t; promote to std::uint32_t for bit ops
    return static_cast<std::uint32_t>(static_cast<std::uint16_t>(item));
}
}  // namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score}
{
}

auto allergy_test::is_allergic_to(allergen item) const noexcept -> bool
{
    const std::uint32_t mask = mask_for(item);
    return ((m_score & mask) != static_cast<std::uint32_t>(0));
}

auto allergy_test::get_allergies() const -> allergen_set
{
    allergen_set result{};
    for (const auto item : kAllergens) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies
