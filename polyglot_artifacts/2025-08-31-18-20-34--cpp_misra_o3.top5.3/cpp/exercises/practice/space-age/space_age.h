#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

/*
 * Class that converts an age given in seconds into planetary years.
 * All calculations follow the orbital periods supplied in the exercise
 * description.  Floating-point conversions are performed explicitly to
 * comply with MISRA C++ rules regarding implicit integral-to-floating
 * conversions.
 */
class space_age
{
public:
    explicit space_age(std::uint64_t seconds_in) noexcept;

    std::uint64_t seconds() const noexcept;

    double on_mercury() const noexcept;
    double on_venus()   const noexcept;
    double on_earth()   const noexcept;
    double on_mars()    const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn()  const noexcept;
    double on_uranus()  const noexcept;
    double on_neptune() const noexcept;

private:
    std::uint64_t seconds_value_;
    static constexpr double earth_year_seconds = 31'557'600.0;
};

} // namespace space_age

#endif // SPACE_AGE_H
