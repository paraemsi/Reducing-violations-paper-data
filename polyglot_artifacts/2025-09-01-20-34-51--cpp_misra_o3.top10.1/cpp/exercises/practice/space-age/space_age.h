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
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    std::uint64_t seconds_{0U};

    static constexpr double earth_year_seconds{31557600.0};

    static constexpr double mercury_orbital_ratio{0.2408467};
    static constexpr double venus_orbital_ratio{0.61519726};
    static constexpr double mars_orbital_ratio{1.8808158};
    static constexpr double jupiter_orbital_ratio{11.862615};
    static constexpr double saturn_orbital_ratio{29.447498};
    static constexpr double uranus_orbital_ratio{84.016846};
    static constexpr double neptune_orbital_ratio{164.79132};
};

} // namespace space_age

#endif // SPACE_AGE_H
