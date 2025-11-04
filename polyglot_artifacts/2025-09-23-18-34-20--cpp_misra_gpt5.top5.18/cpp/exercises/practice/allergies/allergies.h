#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <functional>

namespace allergies {

// Enumerates the known allergens with power-of-two bit values.
enum class allergy : std::uint16_t {
    eggs = static_cast<std::uint16_t>(1U),
    peanuts = static_cast<std::uint16_t>(2U),
    shellfish = static_cast<std::uint16_t>(4U),
    strawberries = static_cast<std::uint16_t>(8U),
    tomatoes = static_cast<std::uint16_t>(16U),
    chocolate = static_cast<std::uint16_t>(32U),
    pollen = static_cast<std::uint16_t>(64U),
    cats = static_cast<std::uint16_t>(128U)
};
 

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(allergy item) const noexcept;

    std::unordered_set<allergy> get_allergies() const;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

// Enable std::unordered_set for allergies::allergen
namespace std {
template <>
struct hash<allergies::allergy> {
    std::size_t operator()(allergies::allergy a) const noexcept {
        return static_cast<std::size_t>(static_cast<std::uint16_t>(a));
    }
};
}  // namespace std

#endif // ALLERGIES_H
