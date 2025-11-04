#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

using age_seconds_t = std::int64_t;

class space_age {
private:
    age_seconds_t age_seconds;
public:
    explicit space_age(age_seconds_t seconds);
    age_seconds_t seconds() const;
    double on_mercury() const;
    double on_venus() const;
    double on_earth() const;
    double on_mars() const;
    double on_jupiter() const;
    double on_saturn() const;
    double on_uranus() const;
    double on_neptune() const;
};

}  // namespace space_age

#endif // SPACE_AGE_H
