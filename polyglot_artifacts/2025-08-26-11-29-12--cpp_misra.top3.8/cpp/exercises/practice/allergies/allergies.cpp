#include "allergies.h"

#include <utility>

namespace allergies {

namespace
{
    struct allergen_info
    {
        const char* name;
        allergy_score_t value;
    };

    // List of allergens and their values
    constexpr allergen_info allergen_table[] = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };

    constexpr std::size_t allergen_count = sizeof(allergen_table) / sizeof(allergen_table[0]);
}

allergy_test::allergy_test(allergy_score_t score_in)
    : score(score_in)
{
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if(allergen == allergen_table[i].name)
        {
            return ((score & allergen_table[i].value) != 0U);
        }
    }
    return false;
}

std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> result;
    for(std::size_t i = 0U; i < allergen_count; ++i)
    {
        if((score & allergen_table[i].value) != 0U)
        {
            result.emplace_back(allergen_table[i].name);
        }
    }
    // Sort the result to allow comparison with unordered_set in tests
    std::sort(result.begin(), result.end());
    return result;
}

}  // namespace allergies
