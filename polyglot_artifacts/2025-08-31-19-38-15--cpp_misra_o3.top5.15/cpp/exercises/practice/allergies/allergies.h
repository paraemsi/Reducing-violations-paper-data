#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

using score_t = std::uint32_t;

class allergy_test {
public:
    explicit allergy_test(score_t score_value) noexcept;

    bool is_allergic_to(const std::string &item) const;

    std::unordered_set<std::string> get_allergies() const;

private:
    score_t const m_score;

    static score_t allergen_value(const std::string &item);
};

}  // namespace allergies

#endif // ALLERGIES_H
