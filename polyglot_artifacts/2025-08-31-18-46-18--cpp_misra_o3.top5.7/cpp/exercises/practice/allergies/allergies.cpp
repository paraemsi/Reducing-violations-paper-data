#include "allergies.h"

#include <string_view>
#include <string>
#include <unordered_map>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score} { }

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    return ((static_cast<std::uint32_t>(item) & m_score) != 0U);
}

bool allergy_test::is_allergic_to(std::string_view item) const {
    static const std::unordered_map<std::string_view, allergen> lookup{
        { "eggs", allergen::eggs }, { "peanuts", allergen::peanuts },
        { "shellfish", allergen::shellfish }, { "strawberries", allergen::strawberries },
        { "tomatoes", allergen::tomatoes }, { "chocolate", allergen::chocolate },
        { "pollen", allergen::pollen }, { "cats", allergen::cats }
    };

    auto const it{ lookup.find(item) };
    if (it == lookup.end()) {
        return false;
    }

    return is_allergic_to(it->second);
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result{};
    for (auto const& name : { "eggs", "peanuts", "shellfish", "strawberries",
                              "tomatoes", "chocolate", "pollen", "cats" }) {
        if (is_allergic_to(name)) {
            result.emplace(name);
        }
    }
    return result;
}

}  // namespace allergies
