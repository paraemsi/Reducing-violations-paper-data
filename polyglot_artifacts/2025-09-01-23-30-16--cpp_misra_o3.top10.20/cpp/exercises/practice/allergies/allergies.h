#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <functional>
#include <unordered_set>

namespace allergies {

// Enumeration of allergens with the score assigned to each one.
// A fixed-width unsigned type is used to respect MISRA rules.
enum class allergen : std::uint32_t {
    eggs         = 1U,
    peanuts      = 2U,
    shellfish    = 4U,
    strawberries = 8U,
    tomatoes     = 16U,
    chocolate    = 32U,
    pollen       = 64U,
    cats         = 128U
};

// Class that represents the outcome of an allergy test.
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const noexcept;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

// Hash specialisation that enables the use of allergen in unordered containers.
namespace std {
template<>
struct hash<allergies::allergen> {
    size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<size_t>(a);
    }
};
} // namespace std

#endif // ALLERGIES_H
