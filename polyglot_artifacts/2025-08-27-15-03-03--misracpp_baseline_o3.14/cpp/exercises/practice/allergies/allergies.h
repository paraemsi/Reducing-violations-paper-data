#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstddef>
#include <functional>

namespace allergies {

enum class allergen : unsigned int {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries= 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

class allergy_test {
public:
    explicit allergy_test(unsigned int score) noexcept;

    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const noexcept;

private:
    unsigned int score_;
};

}  // namespace allergies

// Provide std::hash specialization for allergies::allergen so that
// std::unordered_set<allergies::allergen> can be instantiated in any TU
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

#endif // ALLERGIES_H
