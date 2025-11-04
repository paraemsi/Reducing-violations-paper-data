#include "allergies.h"

namespace allergies {

const std::vector<std::string> allergy_test::allergen_list = {
    "eggs",
    "peanuts",
    "shellfish",
    "strawberries",
    "tomatoes",
    "chocolate",
    "pollen",
    "cats"
};

allergy_test::allergy_test(allergy_score_t score_in)
    : score(score_in)
{
}

allergy_score_t allergy_test::allergen_score(const std::string& allergen)
{
    for(std::size_t i = 0U; i < allergen_list.size(); ++i)
    {
        if(allergen_list[i] == allergen)
        {
            // Each allergen's score is 1 << i
            return static_cast<allergy_score_t>(1U << i);
        }
    }
    return 0U;
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    allergy_score_t mask = allergen_score(allergen);
    return ((mask != 0U) && ((score & mask) != 0U));
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result;
    for(std::size_t i = 0U; i < allergen_list.size(); ++i)
    {
        allergy_score_t mask = static_cast<allergy_score_t>(1U << i);
        if((score & mask) != 0U)
        {
            result.emplace(allergen_list[i]);
        }
    }
    return result;
}

}  // namespace allergies
