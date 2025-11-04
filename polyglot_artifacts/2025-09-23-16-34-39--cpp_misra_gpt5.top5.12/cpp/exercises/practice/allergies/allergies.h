#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <functional>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint8_t {
    eggs = static_cast<std::uint8_t>(1U),
    peanuts = static_cast<std::uint8_t>(2U),
    shellfish = static_cast<std::uint8_t>(4U),
    strawberries = static_cast<std::uint8_t>(8U),
    tomatoes = static_cast<std::uint8_t>(16U),
    chocolate = static_cast<std::uint8_t>(32U),
    pollen = static_cast<std::uint8_t>(64U),
    cats = static_cast<std::uint8_t>(128U)
};

struct allergen_hash {
    std::size_t operator()(allergen a) const noexcept {
        return static_cast<std::size_t>(static_cast<std::uint8_t>(a));
    }
};

using allergen_set = std::unordered_set<allergen, allergen_hash>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    allergen_set get_allergies() const;
private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
