#include "allergies.h"

namespace allergies {

namespace {
    struct allergen_info {
        const char* name;
        score_type value;
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

allergy_test::allergy_test(score_type score_in)
    : score(score_in)
{
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    for(std::size_t i = 0U; i < allergen_count; ++i) {
        if(allergen == allergen_table[i].name) {
            return ((score & allergen_table[i].value) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result;
    for(std::size_t i = 0U; i < allergen_count; ++i) {
        if((score & allergen_table[i].value) != 0U) {
            result.emplace(allergen_table[i].name);
        }
    }
    return result;
}

}  // namespace allergies
