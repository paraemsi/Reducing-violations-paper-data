#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age
{
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    [[nodiscard]] std::uint64_t seconds() const noexcept;

    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus()   const noexcept;
    [[nodiscard]] double on_earth()   const noexcept;
    [[nodiscard]] double on_mars()    const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn()  const noexcept;
    [[nodiscard]] double on_uranus()  const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    std::uint64_t m_seconds;

    static constexpr double earth_year_seconds = 31'557'600.0;

    static constexpr double mercury_period = 0.2408467;
    static constexpr double venus_period   = 0.61519726;
    static constexpr double earth_period   = 1.0;
    static constexpr double mars_period    = 1.8808158;
    static constexpr double jupiter_period = 11.862615;
    static constexpr double saturn_period  = 29.447498;
    static constexpr double uranus_period  = 84.016846;
    static constexpr double neptune_period = 164.79132;

    [[nodiscard]] double age_on(double orbital_period) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
