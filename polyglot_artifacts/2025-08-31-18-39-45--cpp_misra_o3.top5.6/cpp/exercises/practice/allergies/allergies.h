#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <array>
#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <vector>
#include <functional>
#include <string>

namespace allergies {

// Fixed-width integral representation for each allergen (MISRA compliant)
enum class Allergen : std::uint8_t
{
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
 * Provide a std::hash specialisation for the Allergen enum so that it can be
 * used directly as the key type in unordered containers without requiring a
 * custom hasher at every use-site.  The specialisation must reside in the
 * std namespace by rule.
 */
}  // namespace allergies

namespace std {
template <>
struct hash<allergies::Allergen>
{
    std::size_t operator()(const allergies::Allergen& allergen) const noexcept
    {
        return static_cast<std::size_t>(allergen);
    }
};
}  // namespace std

namespace allergies {

// Class that encapsulates an allergy score and related queries
class Allergies
{
public:
    explicit Allergies(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(Allergen allergen) const noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& allergen_name) const noexcept;

    [[nodiscard]] std::vector<std::string> get_allergies() const noexcept;

private:
    std::uint32_t m_score;  // raw bit-field coming from the test
};

// Factory function expected by the unit tests
[[nodiscard]] Allergies allergy_test(std::uint32_t score) noexcept;

}  // namespace allergies

#endif // ALLERGIES_H
