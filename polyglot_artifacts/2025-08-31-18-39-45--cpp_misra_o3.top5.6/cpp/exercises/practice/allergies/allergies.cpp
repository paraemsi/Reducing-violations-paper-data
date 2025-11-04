#include "allergies.h"

#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <cstddef>
#include <functional>

namespace allergies {

// Local helper containing every known allergen
namespace
{
static constexpr std::array<Allergen, 8U> k_all_allergens{
    Allergen::eggs,
    Allergen::peanuts,
    Allergen::shellfish,
    Allergen::strawberries,
    Allergen::tomatoes,
    Allergen::chocolate,
    Allergen::pollen,
    Allergen::cats};
} // unnamed namespace


Allergies::Allergies(std::uint32_t score) noexcept
    : m_score{score}
{
}

bool Allergies::is_allergic_to(Allergen allergen) const noexcept
{
    const std::uint32_t allergen_value{static_cast<std::uint32_t>(allergen)};
    return ((m_score & allergen_value) != 0U);
}

// Overload taking allergen name as a string
bool Allergies::is_allergic_to(const std::string& allergen_name) const noexcept
{
    if (allergen_name == "eggs")
    {
        return is_allergic_to(Allergen::eggs);
    }
    else if (allergen_name == "peanuts")
    {
        return is_allergic_to(Allergen::peanuts);
    }
    else if (allergen_name == "shellfish")
    {
        return is_allergic_to(Allergen::shellfish);
    }
    else if (allergen_name == "strawberries")
    {
        return is_allergic_to(Allergen::strawberries);
    }
    else if (allergen_name == "tomatoes")
    {
        return is_allergic_to(Allergen::tomatoes);
    }
    else if (allergen_name == "chocolate")
    {
        return is_allergic_to(Allergen::chocolate);
    }
    else if (allergen_name == "pollen")
    {
        return is_allergic_to(Allergen::pollen);
    }
    else if (allergen_name == "cats")
    {
        return is_allergic_to(Allergen::cats);
    }

    // Unknown allergen name
    return false;
}

std::vector<std::string> Allergies::get_allergies() const noexcept
{
    std::vector<std::string> result{};
    result.reserve(k_all_allergens.size());
    for (const auto allergen : k_all_allergens)
    {
        if (is_allergic_to(allergen))
        {
            // Map the Allergen enum to its corresponding string representation
            switch (allergen)
            {
                case Allergen::eggs:         result.emplace_back("eggs"); break;
                case Allergen::peanuts:      result.emplace_back("peanuts"); break;
                case Allergen::shellfish:    result.emplace_back("shellfish"); break;
                case Allergen::strawberries: result.emplace_back("strawberries"); break;
                case Allergen::tomatoes:     result.emplace_back("tomatoes"); break;
                case Allergen::chocolate:    result.emplace_back("chocolate"); break;
                case Allergen::pollen:       result.emplace_back("pollen"); break;
                case Allergen::cats:         result.emplace_back("cats"); break;
                default:
                    break;
            }
        }
    }
    return result;
}

// Factory function definition required by unit tests
Allergies allergy_test(std::uint32_t score) noexcept
{
    return Allergies{score};
}

}  // namespace allergies
