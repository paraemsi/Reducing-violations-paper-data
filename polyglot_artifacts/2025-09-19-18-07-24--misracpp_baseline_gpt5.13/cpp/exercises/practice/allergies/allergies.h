#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>
#include <cstddef>
#include <type_traits>

namespace allergies {

enum class allergen : unsigned int {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

}  // namespace allergies

namespace std {
    template <> struct hash<allergies::allergen> {
        std::size_t operator()(const allergies::allergen a) const noexcept {
            using underlying = typename std::underlying_type<allergies::allergen>::type;
            return std::hash<underlying>{}(static_cast<underlying>(a));
        }
    };
}

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(unsigned int score);
    bool is_allergic_to(allergen item) const;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

#endif // ALLERGIES_H
