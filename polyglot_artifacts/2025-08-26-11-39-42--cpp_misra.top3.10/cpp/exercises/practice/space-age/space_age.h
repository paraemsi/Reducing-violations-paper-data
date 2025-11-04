#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

    typedef std::int64_t seconds_t;

    class space_age {
    public:
        explicit space_age(seconds_t seconds) noexcept;

        seconds_t seconds(void) const noexcept;

        double on_mercury(void) const noexcept;
        double on_venus(void) const noexcept;
        double on_earth(void) const noexcept;
        double on_mars(void) const noexcept;
        double on_jupiter(void) const noexcept;
        double on_saturn(void) const noexcept;
        double on_uranus(void) const noexcept;
        double on_neptune(void) const noexcept;

    private:
        seconds_t m_seconds;
        static constexpr double earth_year_seconds = 31557600.0;
        static constexpr double mercury_orbital = 0.2408467;
        static constexpr double venus_orbital   = 0.61519726;
        static constexpr double earth_orbital   = 1.0;
        static constexpr double mars_orbital    = 1.8808158;
        static constexpr double jupiter_orbital = 11.862615;
        static constexpr double saturn_orbital  = 29.447498;
        static constexpr double uranus_orbital  = 84.016846;
        static constexpr double neptune_orbital = 164.79132;
    };

}  // namespace space_age

#endif // SPACE_AGE_H
