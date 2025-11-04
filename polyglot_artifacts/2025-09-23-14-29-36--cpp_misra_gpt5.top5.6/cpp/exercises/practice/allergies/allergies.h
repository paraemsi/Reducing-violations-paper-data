#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = static_cast<std::uint32_t>(1),
    peanuts = static_cast<std::uint32_t>(2),
    shellfish = static_cast<std::uint32_t>(4),
    strawberries = static_cast<std::uint32_t>(8),
    tomatoes = static_cast<std::uint32_t>(16),
    chocolate = static_cast<std::uint32_t>(32),
    pollen = static_cast<std::uint32_t>(64),
    cats = static_cast<std::uint32_t>(128)
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies


#endif // ALLERGIES_H
