#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>
#include <cstddef>     // for std::size_t
#include <functional>  // for std::hash primary template

namespace allergies {

/*
 * Enum listing the allergens that are recognised by the test.
 * The underlying type is std::uint8_t to match the bit-field
 * representation dictated by the exercise specification.
 */
enum class allergen : std::uint8_t {
    eggs         = 1U,
    peanuts      = 2U,
    shellfish    = 4U,
    strawberries = 8U,
    tomatoes     = 16U,
    chocolate    = 32U,
    pollen       = 64U,
    cats         = 128U
};

/*
 * Class that encapsulates an allergy score and offers helpers
 * to query individual allergens or obtain the complete set of
 * known allergens contained in the score.
 */
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& item) const noexcept;

    [[nodiscard]] std::vector<std::string> get_allergies() const noexcept;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

/*
 * Provide a std::hash specialisation so that allergen can be used
 * as the key in an unordered_set / unordered_map.
 */
namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return static_cast<std::size_t>(a);
    }
};
} // namespace std

#endif // ALLERGIES_H
