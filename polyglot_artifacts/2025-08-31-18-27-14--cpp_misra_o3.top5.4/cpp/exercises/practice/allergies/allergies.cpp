#include "allergies.h"
#include <unordered_map>

namespace allergies {

namespace {
    constexpr std::uint32_t EGGS_VALUE         { 1U };
    constexpr std::uint32_t PEANUTS_VALUE      { 2U };
    constexpr std::uint32_t SHELLFISH_VALUE    { 4U };
    constexpr std::uint32_t STRAWBERRIES_VALUE { 8U };
    constexpr std::uint32_t TOMATOES_VALUE     { 16U };
    constexpr std::uint32_t CHOCOLATE_VALUE    { 32U };
    constexpr std::uint32_t POLLEN_VALUE       { 64U };
    constexpr std::uint32_t CATS_VALUE         { 128U };

    const std::unordered_map<std::string, std::uint32_t> ALLERGEN_TABLE{
        { "eggs", EGGS_VALUE },
        { "peanuts", PEANUTS_VALUE },
        { "shellfish", SHELLFISH_VALUE },
        { "strawberries", STRAWBERRIES_VALUE },
        { "tomatoes", TOMATOES_VALUE },
        { "chocolate", CHOCOLATE_VALUE },
        { "pollen", POLLEN_VALUE },
        { "cats", CATS_VALUE }
    };
} // unnamed namespace

Allergies::Allergies(std::uint32_t score) noexcept {
    populate_allergens(score);
}

bool Allergies::is_allergic_to(const std::string& item) const noexcept {
    return (allergens_.find(item) != allergens_.end());
}

std::unordered_set<std::string> Allergies::get_allergies() const noexcept {
    return allergens_;
}

void Allergies::populate_allergens(std::uint32_t score) noexcept {
    for (const auto& allergenPair : ALLERGEN_TABLE) {
        const std::string&   name { allergenPair.first };
        const std::uint32_t  bit  { allergenPair.second };

        if ((score & bit) != 0U) {
            allergens_.emplace(name);
        }
    }
}

Allergies allergy_test(std::uint32_t score) noexcept {
    return Allergies{ score };
}

}  // namespace allergies
