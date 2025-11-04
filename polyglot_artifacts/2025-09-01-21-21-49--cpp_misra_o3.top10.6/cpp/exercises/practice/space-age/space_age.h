#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

// SpaceAge class computes age on different planets given an
// elapsed time in seconds (stored as a 64-bit unsigned integer).
class space_age final {
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
    std::uint64_t seconds_{0U};

    static constexpr double earth_year_seconds{31557600.0};

    static double age_in_years(std::uint64_t seconds, double orbital_ratio) noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
