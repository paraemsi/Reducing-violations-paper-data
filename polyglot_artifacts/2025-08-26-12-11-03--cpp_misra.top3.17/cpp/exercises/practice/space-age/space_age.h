#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(std::int64_t seconds) noexcept;

    std::int64_t seconds() const noexcept;

    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_earth() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    std::int64_t m_seconds;
    static constexpr double earth_year_seconds = 31557600.0;
};

}  // namespace space_age

#endif // SPACE_AGE_H
