#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>
#include <cstddef>
#include <type_traits>

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
    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const;

private:
    unsigned int score_;
};

}  // namespace allergies

// Provide a hash specialization so allergen can be used in unordered containers.
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(allergies::allergen a) const noexcept {
        using U = std::underlying_type_t<allergies::allergen>;
        return std::hash<U>{}(static_cast<U>(a));
    }
};
}  // namespace std

#endif // ALLERGIES_H
