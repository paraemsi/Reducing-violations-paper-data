#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

using seconds_t = std::uint64_t;

class space_age {
public:
    explicit space_age(seconds_t seconds) noexcept;
    seconds_t seconds() const noexcept;

    double on_earth() const noexcept;
    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    seconds_t seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
