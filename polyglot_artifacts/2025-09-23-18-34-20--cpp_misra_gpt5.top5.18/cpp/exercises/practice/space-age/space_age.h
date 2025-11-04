#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    [[nodiscard]] std::uint64_t seconds() const noexcept;

    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    [[nodiscard]] double on_planet(double orbital_period) const noexcept;

    static constexpr double earth_year_seconds = 31557600.0;
    std::uint64_t seconds_{0U};
};

}  // namespace space_age

#endif // SPACE_AGE_H
