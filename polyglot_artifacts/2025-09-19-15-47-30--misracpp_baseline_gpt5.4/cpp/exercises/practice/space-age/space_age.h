#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
public:
    explicit space_age(long long seconds) noexcept;

    long long seconds() const noexcept;

    double on_earth() const noexcept;
    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    static constexpr double seconds_per_earth_year = 31557600.0;

    static constexpr double mercury_period = 0.2408467;
    static constexpr double venus_period   = 0.61519726;
    static constexpr double earth_period   = 1.0;
    static constexpr double mars_period    = 1.8808158;
    static constexpr double jupiter_period = 11.862615;
    static constexpr double saturn_period  = 29.447498;
    static constexpr double uranus_period  = 84.016846;
    static constexpr double neptune_period = 164.79132;

    long long seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
