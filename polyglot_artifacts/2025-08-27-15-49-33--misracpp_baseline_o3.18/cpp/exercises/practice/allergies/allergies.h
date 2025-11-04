#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <array>
#include <type_traits>
#include <cstddef>   // for std::size_t

namespace allergies {

enum class allergen {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

class allergy_test {
public:
    explicit allergy_test(int score);

    bool is_allergic_to(allergen item) const;

    std::unordered_set<allergen> get_allergies() const;

private:
    int score_;
    std::unordered_set<allergen> allergies_;
    static const std::array<allergen, 8> all_allergens;
};

}  // namespace allergies

// Provide a hash specialization so that allergen can be used in unordered containers.
namespace std {
template <>
struct hash<allergies::allergen> {
    size_t operator()(const allergies::allergen& a) const noexcept {
        using underlying = std::underlying_type_t<allergies::allergen>;
        return static_cast<size_t>(static_cast<underlying>(a));
    }
};
}  // namespace std

#endif // ALLERGIES_H
