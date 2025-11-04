#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>

namespace allergies {

class Allergies final
{
public:
    explicit Allergies(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const noexcept;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const noexcept;

private:
    std::uint32_t m_score;

    static const std::unordered_map<std::string, std::uint32_t> s_allergen_values;
};

Allergies allergy_test(std::uint32_t score) noexcept;

}  // namespace allergies

#endif // ALLERGIES_H
