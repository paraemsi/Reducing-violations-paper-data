#ifndef ALLERGIES_H
#define ALLERGIES_H
#pragma once
#include <unordered_set>
#include <type_traits>
#include <functional>
#include <cstddef>

namespace allergies {

enum class allergen {
    eggs,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

class allergy_test {
public:
    explicit allergy_test(unsigned int score);
    bool is_allergic_to(allergen a) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::allergen> {
    size_t operator()(const allergies::allergen& a) const noexcept {
        using U = std::underlying_type<allergies::allergen>::type;
        return std::hash<U>{}(static_cast<U>(a));
    }
};
}

#endif // ALLERGIES_H
