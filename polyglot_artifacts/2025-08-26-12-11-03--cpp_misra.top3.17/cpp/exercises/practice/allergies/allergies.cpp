#include "allergies.h"

namespace allergies {

namespace {
    struct Allergen {
        const char* name;
        std::uint32_t value;
    };

    // List of allergens and their values
    constexpr Allergen allergen_list[] = {
        {"eggs", 1u},
        {"peanuts", 2u},
        {"shellfish", 4u},
        {"strawberries", 8u},
        {"tomatoes", 16u},
        {"chocolate", 32u},
        {"pollen", 64u},
        {"cats", 128u}
    };

    constexpr std::size_t allergen_count = sizeof(allergen_list) / sizeof(Allergen);
}

Allergies::Allergies(std::uint32_t score_in)
    : score_(score_in), allergy_set_()
{
    parse_score();
}

void Allergies::parse_score(void)
{
    for(std::size_t i = 0u; i < allergen_count; ++i) {
        if(((score_ & allergen_list[i].value) != 0u)) {
            allergy_set_.emplace(allergen_list[i].name);
        }
    }
}

bool Allergies::is_allergic_to(const std::string& allergen) const
{
    return (allergy_set_.find(allergen) != allergy_set_.end());
}

std::vector<std::string> Allergies::list(void) const
{
    std::vector<std::string> result;
    for(std::size_t i = 0u; i < allergen_count; ++i) {
        if(((score_ & allergen_list[i].value) != 0u)) {
            result.emplace_back(allergen_list[i].name);
        }
    }
    return result;
}

// For test compatibility: get_allergies() alias for list()
std::vector<std::string> Allergies::get_allergies(void) const
{
    return list();
}

Allergies allergy_test(std::uint32_t score)
{
    return Allergies(score);
}

}  // namespace allergies
