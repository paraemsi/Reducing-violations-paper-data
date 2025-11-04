#include "allergies.h"

namespace allergies {

namespace
{
    struct AllergenInfo
    {
        const char* name;
        allergy_score_t value;
    };

    constexpr AllergenInfo allergen_table[] = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };

    constexpr std::size_t allergen_count = sizeof(allergen_table) / sizeof(AllergenInfo);
}

Allergies::Allergies(allergy_score_t score)
    : m_score(static_cast<allergy_score_t>(score & 0xFFU)) // Only keep the lowest 8 bits
{
}

bool Allergies::is_allergic_to(const std::string& allergen) const
{
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if(allergen == allergen_table[i].name)
        {
            return ((m_score & allergen_table[i].value) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> Allergies::get_allergies() const
{
    std::unordered_set<std::string> result;
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if((m_score & allergen_table[i].value) != 0U)
        {
            result.emplace(allergen_table[i].name);
        }
    }
    return result;
}

}  // namespace allergies
