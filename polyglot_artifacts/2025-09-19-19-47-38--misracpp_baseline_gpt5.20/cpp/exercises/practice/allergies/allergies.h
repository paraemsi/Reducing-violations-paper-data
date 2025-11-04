#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <unordered_set>
#include <cstddef>
#include <functional>

namespace allergies {

enum class allergen : unsigned int {
    eggs = 1u,
    peanuts = 2u,
    shellfish = 4u,
    strawberries = 8u,
    tomatoes = 16u,
    chocolate = 32u,
    pollen = 64u,
    cats = 128u
};


class allergy_test {
public:
    explicit allergy_test(unsigned int score) noexcept;

    bool is_allergic_to(allergen a) const noexcept;

    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

namespace std {
template<>
struct hash<allergies::allergen> {
    size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<size_t>(a);
    }
};
} // namespace std

#endif // ALLERGIES_H
