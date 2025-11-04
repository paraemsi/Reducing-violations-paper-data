#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class Allergies {
public:
    explicit Allergies(std::uint16_t score);

    bool is_allergic_to(const std::string& allergen) const;
    std::vector<std::string> get_allergies() const;

private:
    std::unordered_set<std::string> allergies_;
    static const std::vector<std::pair<std::string, std::uint16_t> >& allergen_list();
};

// Factory function to match test expectations
Allergies allergy_test(std::uint16_t score);

}  // namespace allergies

#endif // ALLERGIES_H
