#include "allergies.h"
#include <cstdint>
#include <array>
#include <unordered_set>
#include <string>


namespace allergies {

static constexpr const char* allergen_to_string(allergen value) noexcept
{
    switch (value)
    {
        case allergen::eggs:         return "eggs";
        case allergen::peanuts:      return "peanuts";
        case allergen::shellfish:    return "shellfish";
        case allergen::strawberries: return "strawberries";
        case allergen::tomatoes:     return "tomatoes";
        case allergen::chocolate:    return "chocolate";
        case allergen::pollen:       return "pollen";
        case allergen::cats:         return "cats";
        default:                     return "";
    }
}

static constexpr std::array<allergen, 8U> all_allergens{
    {allergen::eggs, allergen::peanuts,   allergen::shellfish, allergen::strawberries,
     allergen::tomatoes, allergen::chocolate, allergen::pollen, allergen::cats}};

allergy_test::allergy_test(std::uint32_t score) noexcept : m_score{score}
{
}

bool allergy_test::is_allergic_to(allergen allergen_value) const noexcept
{
    return ((m_score & static_cast<std::uint32_t>(allergen_value)) != 0U);
}

bool allergy_test::is_allergic_to(const std::string& allergen_name) const noexcept
{
    for (const auto& item : all_allergens) {
        if (allergen_name == allergen_to_string(item)) {
            return is_allergic_to(item);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<std::string> result{};
    for (const auto& item : all_allergens) {
        if ((m_score & static_cast<std::uint32_t>(item)) != 0U) {
            (void)result.emplace(allergen_to_string(item));
        }
    }
    return result;
}

}  // namespace allergies
