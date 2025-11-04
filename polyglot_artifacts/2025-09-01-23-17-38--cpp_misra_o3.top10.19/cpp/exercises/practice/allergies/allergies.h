#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <functional>

namespace allergies {

enum class allergen : std::uint32_t
{
  eggs        = 1U,
  peanuts     = 2U,
  shellfish   = 4U,
  strawberries= 8U,
  tomatoes    = 16U,
  chocolate   = 32U,
  pollen      = 64U,
  cats        = 128U
};

using score_type = std::uint32_t;

class allergy_test final
{
public:
  explicit allergy_test(score_type score) noexcept;

  [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

  [[nodiscard]] std::unordered_set<allergen> get_allergies() const;

private:
  score_type m_score;
};

}  // namespace allergies


// Provide a hash specialisation so that allergen can be used in an
// unordered associative container.  This is permitted by the C++
// Standard (§20.14.15) for user-defined types.
namespace std {

template<>
struct hash<::allergies::allergen>
{
  std::size_t operator()(::allergies::allergen a) const noexcept
  {
    return static_cast<std::size_t>(a);
  }
};

}  // namespace std

#endif // ALLERGIES_H
