#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <string_view>
#include <string>

namespace allergies {

// All allergens covered by the test and their bit-mask values
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


class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    // Return true if the stored score contains the given allergen name
    bool is_allergic_to(std::string_view item) const;

    // Return a set with every allergen name contained in the stored score
    std::unordered_set<std::string> get_allergies() const;

private:
    // Helper working directly with the strongly-typed id
    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
