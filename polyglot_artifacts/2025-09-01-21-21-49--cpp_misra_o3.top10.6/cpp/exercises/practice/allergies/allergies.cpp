#include "allergies.h"
#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

namespace allergies {

/*  Helper mapping between string names and enum values – created once
 *  and reused. Declared `static` inside the namespace for internal linkage.
 */
static const std::unordered_map<std::string, allergen>& name_to_enum() noexcept
{
    static const std::unordered_map<std::string, allergen> map{
        {"eggs",         allergen::eggs},
        {"peanuts",      allergen::peanuts},
        {"shellfish",    allergen::shellfish},
        {"strawberries", allergen::strawberries},
        {"tomatoes",     allergen::tomatoes},
        {"chocolate",    allergen::chocolate},
        {"pollen",       allergen::pollen},
        {"cats",         allergen::cats}
    };
    return map;
}

allergy::allergy(std::uint32_t score_in) noexcept
    : score_(score_in) { }

bool allergy::is_allergic_to(allergen item) const noexcept
{
    /*  Parenthesised to satisfy precedence rule MISRA */
    return ((score_ & static_cast<std::uint32_t>(item)) != 0U);
}

std::vector<allergen> allergy::get_allergies() const noexcept
{
    std::vector<allergen> result{};

    /*  Check each known allergen and populate the set  */
    if (is_allergic_to(allergen::eggs)) {
        result.push_back(allergen::eggs);
    }
    if (is_allergic_to(allergen::peanuts)) {
        result.push_back(allergen::peanuts);
    }
    if (is_allergic_to(allergen::shellfish)) {
        result.push_back(allergen::shellfish);
    }
    if (is_allergic_to(allergen::strawberries)) {
        result.push_back(allergen::strawberries);
    }
    if (is_allergic_to(allergen::tomatoes)) {
        result.push_back(allergen::tomatoes);
    }
    if (is_allergic_to(allergen::chocolate)) {
        result.push_back(allergen::chocolate);
    }
    if (is_allergic_to(allergen::pollen)) {
        result.push_back(allergen::pollen);
    }
    if (is_allergic_to(allergen::cats)) {
        result.push_back(allergen::cats);
    }

    return result;
}

/* ------------------------------------------------------------------ */
/*              wrapper: allergies::allergy_test methods              */
/* ------------------------------------------------------------------ */

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : impl_{score_in} { }

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    const auto& mapping = name_to_enum();
    const auto it = mapping.find(item);
    if (it == mapping.end()) {
        return false;
    }
    return impl_.is_allergic_to(it->second);
}

std::unordered_set<std::string> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<std::string> result{};
    const auto& mapping = name_to_enum();
    for (const auto& kv : mapping) {
        if (impl_.is_allergic_to(kv.second)) {
            result.emplace(kv.first);
        }
    }
    return result;
}

}  // namespace allergies
