#include "allergies.h"

#include <array>
#include <cstdint>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score} {}

bool allergy_test::is_allergic_to(allergy item) const noexcept
{
    return ((score_ & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0U));
}

allergy_set allergy_test::get_allergies() const
{
    static constexpr std::array<allergy, 8U> all_items = {
        allergy::eggs,
        allergy::peanuts,
        allergy::shellfish,
        allergy::strawberries,
        allergy::tomatoes,
        allergy::chocolate,
        allergy::pollen,
        allergy::cats
    };

    allergy_set result{};
    for (const auto& a : all_items) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies
