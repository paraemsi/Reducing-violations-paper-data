#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class Allergies {
public:
    using score_type = std::uint16_t;

    explicit Allergies(score_type score);

    bool is_allergic_to(const std::string& allergen) const;

    std::vector<std::string> get_allergies() const;

private:
    score_type m_score;
    static std::vector<std::string> allergen_list;
    static std::vector<score_type> allergen_values;
};

// Factory function for test compatibility
Allergies allergy_test(Allergies::score_type score);

}  // namespace allergies

#endif // ALLERGIES_H
