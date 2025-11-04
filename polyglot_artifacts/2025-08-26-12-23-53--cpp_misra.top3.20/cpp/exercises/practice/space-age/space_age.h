#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

    typedef std::int64_t seconds_t;

    class space_age {
    public:
        explicit space_age(seconds_t seconds);

        seconds_t seconds() const;

        double on_mercury() const;
        double on_venus() const;
        double on_earth() const;
        double on_mars() const;
        double on_jupiter() const;
        double on_saturn() const;
        double on_uranus() const;
        double on_neptune() const;

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
