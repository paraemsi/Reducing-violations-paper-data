#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& item) const;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
