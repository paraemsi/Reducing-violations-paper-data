#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

using score_type = std::uint16_t;

class allergy_test
{
public:
    explicit allergy_test(score_type score_in);

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const;
    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    score_type score;
};

}  // namespace allergies

#endif // ALLERGIES_H
