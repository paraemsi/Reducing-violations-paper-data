#include "allergies.h"

namespace allergies {

namespace
{
    struct allergen_info
    {
        const char* name;
        score_type value;
    };

    constexpr allergen_info allergen_table[] = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };

    constexpr std::size_t allergen_count = sizeof(allergen_table) / sizeof(allergen_table[0]);
}

allergy_test::allergy_test(score_type score_in)
    : score(score_in)
{
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if((allergen == allergen_table[i].name) && ((score & allergen_table[i].value) != 0U))
        {
            return true;
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result;
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if((score & allergen_table[i].value) != 0U)
        {
            result.emplace(allergen_table[i].name);
        }
    }
    return result;
}

}  // namespace allergies
