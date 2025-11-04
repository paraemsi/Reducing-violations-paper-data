#include "allergies.h"

#include <array>
#include <string>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    return ((m_score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::list() const
{
    std::unordered_set<allergen> result{};
    result.reserve(8U);

    constexpr std::array<allergen, 8U> items{
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (const auto a : items) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }

    return result;
}

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    if ((item == std::string("eggs"))) {
        return is_allergic_to(allergen::eggs);
    } else if ((item == std::string("peanuts"))) {
        return is_allergic_to(allergen::peanuts);
    } else if ((item == std::string("shellfish"))) {
        return is_allergic_to(allergen::shellfish);
    } else if ((item == std::string("strawberries"))) {
        return is_allergic_to(allergen::strawberries);
    } else if ((item == std::string("tomatoes"))) {
        return is_allergic_to(allergen::tomatoes);
    } else if ((item == std::string("chocolate"))) {
        return is_allergic_to(allergen::chocolate);
    } else if ((item == std::string("pollen"))) {
        return is_allergic_to(allergen::pollen);
    } else if ((item == std::string("cats"))) {
        return is_allergic_to(allergen::cats);
    } else {
        return false;
    }
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    result.reserve(8U);

    if (is_allergic_to(allergen::eggs)) {
        result.emplace(std::string("eggs"));
    }
    if (is_allergic_to(allergen::peanuts)) {
        result.emplace(std::string("peanuts"));
    }
    if (is_allergic_to(allergen::shellfish)) {
        result.emplace(std::string("shellfish"));
    }
    if (is_allergic_to(allergen::strawberries)) {
        result.emplace(std::string("strawberries"));
    }
    if (is_allergic_to(allergen::tomatoes)) {
        result.emplace(std::string("tomatoes"));
    }
    if (is_allergic_to(allergen::chocolate)) {
        result.emplace(std::string("chocolate"));
    }
    if (is_allergic_to(allergen::pollen)) {
        result.emplace(std::string("pollen"));
    }
    if (is_allergic_to(allergen::cats)) {
        result.emplace(std::string("cats"));
    }

    return result;
}

}  // namespace allergies
