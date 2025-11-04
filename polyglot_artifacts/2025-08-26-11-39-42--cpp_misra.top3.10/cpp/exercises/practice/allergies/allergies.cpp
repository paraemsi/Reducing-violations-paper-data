#include "allergies.h"

namespace allergies {

const std::vector<std::string>& allergy_test::get_allergen_list()
{
    static const std::vector<std::string> allergen_list = {
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    };
    return allergen_list;
}

allergy_test::allergy_test(allergy_score_t score)
    : m_score(score)
{
}

allergy_score_t allergy_test::allergen_score(const std::string& allergen)
{
    const std::vector<std::string>& list = get_allergen_list();
    for(std::size_t i = 0U; i < list.size(); ++i)
    {
        if(list[i] == allergen)
        {
            // Each allergen's score is 1 << i
            return static_cast<allergy_score_t>(1U << i);
        }
    }
    return 0U;
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    allergy_score_t score = allergen_score(allergen);
    return ((score != 0U) && ((m_score & score) != 0U));
}

std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> result;
    const std::vector<std::string>& list = get_allergen_list();
    for(std::size_t i = 0U; i < list.size(); ++i)
    {
        allergy_score_t score = static_cast<allergy_score_t>(1U << i);
        if((m_score & score) != 0U)
        {
            result.emplace_back(list[i]);
        }
    }
    // Sort result to allow unordered_set comparison in tests
    std::sort(result.begin(), result.end());
    return result;
}

}  // namespace allergies
