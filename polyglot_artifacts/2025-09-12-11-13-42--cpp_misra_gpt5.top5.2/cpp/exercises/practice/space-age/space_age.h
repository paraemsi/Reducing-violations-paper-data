#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

using seconds_type = std::int64_t;
using years_type = double;

class space_age {
public:
    explicit space_age(seconds_type seconds) noexcept;
    seconds_type seconds() const noexcept;

    years_type on_earth() const noexcept;
    years_type on_mercury() const noexcept;
    years_type on_venus() const noexcept;
    years_type on_mars() const noexcept;
    years_type on_jupiter() const noexcept;
    years_type on_saturn() const noexcept;
    years_type on_uranus() const noexcept;
    years_type on_neptune() const noexcept;

private:
    seconds_type seconds_{0};
    years_type earth_years_{0.0};

    static constexpr years_type kEarthYearSeconds = 31557600.0;
};

}  // namespace space_age

#endif // SPACE_AGE_H
