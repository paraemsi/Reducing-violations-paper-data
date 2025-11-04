#include "allergies.h"

#include <array>

namespace allergies {

namespace {
constexpr std::uint32_t mask_lower_eight_bits = static_cast<std::uint32_t>(0xFFU);

constexpr std::array<allergen, 8U> all_items{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
};
}  // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(static_cast<std::uint32_t>(score & mask_lower_eight_bits)) {
}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    const std::uint32_t flag = static_cast<std::uint32_t>(static_cast<std::uint8_t>(item));
    return ((m_score & flag) != static_cast<std::uint32_t>(0U));
}

allergen_set allergy_test::get_allergies() const {
    allergen_set result;
    result.reserve(8U);
    for (const auto item : all_items) {
        if (is_allergic_to(item)) {
            (void)result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies
