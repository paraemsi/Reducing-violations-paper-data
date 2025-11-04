#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H
#include <cstdint>

namespace space_age {

class space_age
{
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
    [[nodiscard]] double on_planet(double orbital_factor) const noexcept;

    std::uint64_t m_seconds;
    static constexpr double seconds_per_earth_year = 31'557'600.0; // 365.25 days
};

}  // namespace space_age

#endif // SPACE_AGE_H
