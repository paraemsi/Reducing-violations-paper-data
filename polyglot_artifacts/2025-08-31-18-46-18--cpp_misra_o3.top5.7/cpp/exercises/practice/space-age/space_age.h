#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::int64_t seconds) noexcept;

    [[nodiscard]] auto seconds() const noexcept -> std::int64_t;

    [[nodiscard]] auto on_earth()   const noexcept -> double;
    [[nodiscard]] auto on_mercury() const noexcept -> double;
    [[nodiscard]] auto on_venus()   const noexcept -> double;
    [[nodiscard]] auto on_mars()    const noexcept -> double;
    [[nodiscard]] auto on_jupiter() const noexcept -> double;
    [[nodiscard]] auto on_saturn()  const noexcept -> double;
    [[nodiscard]] auto on_uranus()  const noexcept -> double;
    [[nodiscard]] auto on_neptune() const noexcept -> double;

private:
    std::int64_t seconds_;

    static constexpr double earth_year_seconds = 31'557'600.0; // 365.25 * 24 * 60 * 60

    static constexpr double mercury_orbital_ratio = 0.2408467;
    static constexpr double venus_orbital_ratio   = 0.61519726;
    static constexpr double mars_orbital_ratio    = 1.8808158;
    static constexpr double jupiter_orbital_ratio = 11.862615;
    static constexpr double saturn_orbital_ratio  = 29.447498;
    static constexpr double uranus_orbital_ratio  = 84.016846;
    static constexpr double neptune_orbital_ratio = 164.79132;
};

}  // namespace space_age

#endif // SPACE_AGE_H
