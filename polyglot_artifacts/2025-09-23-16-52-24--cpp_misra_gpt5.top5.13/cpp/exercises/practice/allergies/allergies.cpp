#include "allergies.h"

#include <array>

namespace {
constexpr std::uint32_t mask_for(allergies::allergen a) noexcept {
    switch (a) {
        case allergies::allergen::eggs: {
            return static_cast<std::uint32_t>(1);
        }
        case allergies::allergen::peanuts: {
            return static_cast<std::uint32_t>(2);
        }
        case allergies::allergen::shellfish: {
            return static_cast<std::uint32_t>(4);
        }
        case allergies::allergen::strawberries: {
            return static_cast<std::uint32_t>(8);
        }
        case allergies::allergen::tomatoes: {
            return static_cast<std::uint32_t>(16);
        }
        case allergies::allergen::chocolate: {
            return static_cast<std::uint32_t>(32);
        }
        case allergies::allergen::pollen: {
            return static_cast<std::uint32_t>(64);
        }
        case allergies::allergen::cats: {
            return static_cast<std::uint32_t>(128);
        }
        default: {
            return static_cast<std::uint32_t>(0);
        }
    }
}

constexpr std::array<allergies::allergen, 8U> ALL_ALLERGENS = {
    allergies::allergen::eggs,
    allergies::allergen::peanuts,
    allergies::allergen::shellfish,
    allergies::allergen::strawberries,
    allergies::allergen::tomatoes,
    allergies::allergen::chocolate,
    allergies::allergen::pollen,
    allergies::allergen::cats
};
}  // namespace

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score} {}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    const std::uint32_t m = mask_for(item);
    return ((score_ & m) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};
    for (const auto a : ALL_ALLERGENS) {
        if (is_allergic_to(a)) {
            result.emplace(a);
        }
    }
    return result;
}

}  // namespace allergies
