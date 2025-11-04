#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

#if (__cplusplus >= 201703L)
#define SA_NODISCARD [[nodiscard]]
#else
#define SA_NODISCARD
#endif

namespace space_age {

class space_age {
public:
    explicit space_age(std::int64_t seconds) noexcept;

    SA_NODISCARD std::int64_t seconds() const noexcept;

    SA_NODISCARD double on_mercury() const noexcept;
    SA_NODISCARD double on_venus() const noexcept;
    SA_NODISCARD double on_earth() const noexcept;
    SA_NODISCARD double on_mars() const noexcept;
    SA_NODISCARD double on_jupiter() const noexcept;
    SA_NODISCARD double on_saturn() const noexcept;
    SA_NODISCARD double on_uranus() const noexcept;
    SA_NODISCARD double on_neptune() const noexcept;

private:
    std::int64_t m_seconds;
    static constexpr double earth_year_seconds = 31557600.0;

    SA_NODISCARD double age_on_planet(double orbital_period) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
