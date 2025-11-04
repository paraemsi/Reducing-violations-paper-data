#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::int64_t seconds) noexcept;

    [[nodiscard]] std::int64_t seconds(void) const noexcept;

    [[nodiscard]] double on_earth(void) const noexcept;
    [[nodiscard]] double on_mercury(void) const noexcept;
    [[nodiscard]] double on_venus(void) const noexcept;
    [[nodiscard]] double on_mars(void) const noexcept;
    [[nodiscard]] double on_jupiter(void) const noexcept;
    [[nodiscard]] double on_saturn(void) const noexcept;
    [[nodiscard]] double on_uranus(void) const noexcept;
    [[nodiscard]] double on_neptune(void) const noexcept;

private:
    std::int64_t seconds_;
    static constexpr double kSecondsPerEarthYear { 31557600.0 };
};

}  // namespace space_age

#endif // SPACE_AGE_H
