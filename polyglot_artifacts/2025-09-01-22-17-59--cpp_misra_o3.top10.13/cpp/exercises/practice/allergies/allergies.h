#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(const std::string& allergen) const;

    std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
