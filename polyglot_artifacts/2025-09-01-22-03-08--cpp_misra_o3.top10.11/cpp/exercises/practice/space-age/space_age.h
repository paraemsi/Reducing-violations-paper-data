#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::int64_t seconds) noexcept;

    [[nodiscard]] std::int64_t seconds() const noexcept;

    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    static constexpr double seconds_per_earth_year{31557600.0};

    static constexpr double mercury_ratio{0.2408467};
    static constexpr double venus_ratio{0.61519726};
    static constexpr double earth_ratio{1.0};
    static constexpr double mars_ratio{1.8808158};
    static constexpr double jupiter_ratio{11.862615};
    static constexpr double saturn_ratio{29.447498};
    static constexpr double uranus_ratio{84.016846};
    static constexpr double neptune_ratio{164.79132};

    [[nodiscard]] double on_planet(double orbital_ratio) const noexcept;

    std::int64_t seconds_{0};
};

}  // namespace space_age

#endif // SPACE_AGE_H
