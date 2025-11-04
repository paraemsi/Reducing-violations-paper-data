#include "allergies.h"
#include <string>
#include <unordered_set>

namespace allergies {

namespace
{
    struct MappingEntry
    {
        const char* name;
        Allergen allergen;
    };

    constexpr MappingEntry kMapping[] =
    {
        {"eggs",        Allergen::eggs},
        {"peanuts",     Allergen::peanuts},
        {"shellfish",   Allergen::shellfish},
        {"strawberries",Allergen::strawberries},
        {"tomatoes",    Allergen::tomatoes},
        {"chocolate",   Allergen::chocolate},
        {"pollen",      Allergen::pollen},
        {"cats",        Allergen::cats}
    };
}

Allergies::Allergies(std::uint32_t score_in) noexcept
    : m_score{score_in}
{
}

bool Allergies::is_allergic_to(Allergen allergen) const noexcept
{
    return (((m_score & static_cast<std::uint32_t>(allergen)) != static_cast<std::uint32_t>(0U)));
}

std::vector<Allergen> Allergies::list() const noexcept
{
    std::vector<Allergen> result {};

    for (auto const allergen_value : {
             Allergen::eggs,
             Allergen::peanuts,
             Allergen::shellfish,
             Allergen::strawberries,
             Allergen::tomatoes,
             Allergen::chocolate,
             Allergen::pollen,
             Allergen::cats})
    {
        if (is_allergic_to(allergen_value))
        {
            result.emplace_back(allergen_value);
        }
    }

    return result;
}

bool Allergies::is_allergic_to(const std::string& allergen_name) const noexcept
{
    for (auto const &entry : kMapping)
    {
        if (allergen_name == entry.name)
        {
            return is_allergic_to(entry.allergen);
        }
    }
    return false;
}

std::unordered_set<std::string> Allergies::get_allergies() const noexcept
{
    std::unordered_set<std::string> result_set {};
    for (auto const &entry : kMapping)
    {
        if (is_allergic_to(entry.allergen))
        {
            result_set.emplace(entry.name);
        }
    }
    return result_set;
}

Allergies allergy_test(std::uint32_t score_in) noexcept
{
    return Allergies(score_in);
}

}  // namespace allergies
