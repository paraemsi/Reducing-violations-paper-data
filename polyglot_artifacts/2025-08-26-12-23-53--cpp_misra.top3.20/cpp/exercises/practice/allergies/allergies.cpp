#include "allergies.h"

namespace allergies {

const std::vector<std::string> Allergies::allergen_list = {
    "eggs",
    "peanuts",
    "shellfish",
    "strawberries",
    "tomatoes",
    "chocolate",
    "pollen",
    "cats"
};

const std::vector<Allergies::score_type> Allergies::allergen_values = {
    static_cast<score_type>(1),
    static_cast<score_type>(2),
    static_cast<score_type>(4),
    static_cast<score_type>(8),
    static_cast<score_type>(16),
    static_cast<score_type>(32),
    static_cast<score_type>(64),
    static_cast<score_type>(128)
};

Allergies::Allergies(score_type score)
    : m_score(static_cast<score_type>(score & static_cast<score_type>(255))) // Only keep lower 8 bits
{
}

bool Allergies::is_allergic_to(const std::string& allergen) const
{
    for (std::size_t i = 0U; i < allergen_list.size(); ++i) {
        if (allergen_list[i] == allergen) {
            return ((m_score & allergen_values[i]) != static_cast<score_type>(0));
        }
    }
    return false;
}

std::vector<std::string> Allergies::get_allergies() const
{
    std::vector<std::string> result;
    for (std::size_t i = 0U; i < allergen_list.size(); ++i) {
        if ((m_score & allergen_values[i]) != static_cast<score_type>(0)) {
            result.emplace_back(allergen_list[i]);
        }
    }
    return result;
}

Allergies allergy_test(Allergies::score_type score)
{
    return Allergies(score);
}

}  // namespace allergies
