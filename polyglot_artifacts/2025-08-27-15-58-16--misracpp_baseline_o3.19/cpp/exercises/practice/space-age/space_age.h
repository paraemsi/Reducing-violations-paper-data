#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(int64_t seconds);

    int64_t seconds() const;

    double on_earth() const;
    double on_mercury() const;
    double on_venus() const;
    double on_mars() const;
    double on_jupiter() const;
    double on_saturn() const;
    double on_uranus() const;
    double on_neptune() const;

private:
    static constexpr double earth_year_seconds = 31'557'600.0; // 365.25 days
    int64_t m_seconds;
};

}  // namespace space_age

#endif // SPACE_AGE_H
