#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final {
public:
    using seconds_t = std::uint64_t;
    using real_t = double;

    explicit space_age(seconds_t seconds) noexcept;

    seconds_t seconds() const noexcept;

    real_t on_earth() const noexcept;
    real_t on_mercury() const noexcept;
    real_t on_venus() const noexcept;
    real_t on_mars() const noexcept;
    real_t on_jupiter() const noexcept;
    real_t on_saturn() const noexcept;
    real_t on_uranus() const noexcept;
    real_t on_neptune() const noexcept;

private:
    seconds_t seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
