#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <array>
#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] auto is_allergic_to(const std::string& item) const noexcept -> bool;

    [[nodiscard]] auto get_allergies() const -> std::unordered_set<std::string>;

private:
    std::unordered_set<std::string> m_allergies_set;

    /*  Return a reference to the compile-time mapping of allergen
        names to their bit values.  */
    static auto allergen_map() noexcept
        -> const std::array<std::pair<std::string, std::uint32_t>, 8>&;
};

}  // namespace allergies

#endif // ALLERGIES_H
