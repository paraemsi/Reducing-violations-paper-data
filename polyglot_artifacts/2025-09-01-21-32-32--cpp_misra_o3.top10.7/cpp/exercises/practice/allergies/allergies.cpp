#include "allergies.h"

#include <array>
#include <string>
#include <string_view>
#include <unordered_set>

namespace allergies {

namespace {
static constexpr std::array<std::pair<allergen, std::string_view>, 8U> allergen_map{{
    {allergen::eggs, "eggs"},
    {allergen::peanuts, "peanuts"},
    {allergen::shellfish, "shellfish"},
    {allergen::strawberries, "strawberries"},
    {allergen::tomatoes, "tomatoes"},
    {allergen::chocolate, "chocolate"},
    {allergen::pollen, "pollen"},
    {allergen::cats, "cats"}
}};

static constexpr std::array<allergen, 8U> all_allergens{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};

inline std::string_view to_string(allergen a) noexcept
{
    for (auto const& p : allergen_map)
    {
        if (p.first == a)
        {
            return p.second;
        }
    }
    return {};
}
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : score((score_in & static_cast<std::uint32_t>(255U)))
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0U));
}

bool allergy_test::is_allergic_to(char const* item) const noexcept
{
    std::string_view const sv(item);
    for (auto const& p : allergen_map)
    {
        if (p.second == sv)
        {
            return is_allergic_to(p.first);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    for (auto const& a : all_allergens)
    {
        if (is_allergic_to(a))
        {
            (void)result.emplace(std::string(to_string(a)));
        }
    }
    return result;
}

}  // namespace allergies
