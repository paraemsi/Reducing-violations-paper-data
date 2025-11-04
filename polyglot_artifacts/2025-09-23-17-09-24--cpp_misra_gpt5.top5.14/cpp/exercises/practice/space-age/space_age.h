#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H
#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(double seconds) noexcept;

    double seconds() const noexcept;

    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_earth() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    double seconds_;
    double on_planet(double orbital_period_in_earth_years) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
