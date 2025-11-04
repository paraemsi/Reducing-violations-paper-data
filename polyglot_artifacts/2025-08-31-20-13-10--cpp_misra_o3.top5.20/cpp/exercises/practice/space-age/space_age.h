#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

#if __cplusplus >= 201703L
#define EXERCISM_NODISCARD [[nodiscard]]
#else
#define EXERCISM_NODISCARD
#endif

namespace space_age
{

using second_t = std::int64_t;

class space_age
{
public:
    explicit space_age(second_t seconds_in);
    EXERCISM_NODISCARD second_t seconds() const noexcept;

    EXERCISM_NODISCARD double on_earth() const noexcept;
    EXERCISM_NODISCARD double on_mercury() const noexcept;
    EXERCISM_NODISCARD double on_venus() const noexcept;
    EXERCISM_NODISCARD double on_mars() const noexcept;
    EXERCISM_NODISCARD double on_jupiter() const noexcept;
    EXERCISM_NODISCARD double on_saturn() const noexcept;
    EXERCISM_NODISCARD double on_uranus() const noexcept;
    EXERCISM_NODISCARD double on_neptune() const noexcept;

private:
    second_t m_seconds;
    EXERCISM_NODISCARD double seconds_in_earth_years() const noexcept;
};

} // namespace space_age

#endif // SPACE_AGE_H
