#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstdint>
#include <cstddef>     // for std::size_t
#include <functional>  // for std::hash
#include <string>

namespace allergies {

// Enumeration of known allergens and their associated score value
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

// Class encapsulating an allergy score and related queries
class allergy_test final {
public:
    explicit allergy_test(std::uint32_t score_in) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& item) const noexcept;
    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

// Provide a hash specialization to enable use of `allergen` in unordered containers
namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen a) const noexcept
    {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};
} // namespace std

#endif // ALLERGIES_H
