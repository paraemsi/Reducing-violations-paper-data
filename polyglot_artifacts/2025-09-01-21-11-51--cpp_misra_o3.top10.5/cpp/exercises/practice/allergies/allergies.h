#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

using score_type = std::uint32_t;

class Allergies
{
public:
    explicit Allergies(score_type score) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const noexcept;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const noexcept;

private:
    const score_type m_score;
};

[[nodiscard]] Allergies allergy_test(score_type score) noexcept;

}  // namespace allergies

#endif // ALLERGIES_H
