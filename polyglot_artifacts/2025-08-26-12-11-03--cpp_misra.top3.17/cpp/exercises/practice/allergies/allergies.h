#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

class Allergies {
// MISRA C++: public section first, then private, then any extra public
public:
    explicit Allergies(std::uint32_t score_in);

    bool is_allergic_to(const std::string& allergen) const;
    std::vector<std::string> list(void) const;
    std::vector<std::string> get_allergies(void) const;

private:
// MISRA C++: Use trailing underscores for private data members
    std::uint32_t score_;
    std::unordered_set<std::string> allergy_set_;
    void parse_score(void);
};

// Factory function for test compatibility
Allergies allergy_test(std::uint32_t score);

}  // namespace allergies

#endif // ALLERGIES_H
