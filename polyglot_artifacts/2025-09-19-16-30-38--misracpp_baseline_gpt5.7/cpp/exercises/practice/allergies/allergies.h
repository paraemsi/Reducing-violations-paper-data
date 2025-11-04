#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstddef>
#include <functional>

namespace allergies {

enum class allergen {
    eggs = 0,
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
    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

namespace std {
    template <>
    struct hash<allergies::allergen> {
        size_t operator()(const allergies::allergen& a) const noexcept {
            return static_cast<size_t>(a);
        }
    };
}

#endif // ALLERGIES_H
