#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(std::int64_t seconds) : seconds_{seconds} {}

    std::int64_t seconds() const { return seconds_; }

    double on_earth()   const;
    double on_mercury() const;
    double on_venus()   const;
    double on_mars()    const;
    double on_jupiter() const;
    double on_saturn()  const;
    double on_uranus()  const;
    double on_neptune() const;

private:
    std::int64_t seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
