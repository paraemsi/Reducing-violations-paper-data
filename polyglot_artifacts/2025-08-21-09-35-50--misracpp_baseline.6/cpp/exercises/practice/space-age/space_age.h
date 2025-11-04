#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
public:
    explicit space_age(long long seconds);

    [[nodiscard]] long long seconds() const;

    [[nodiscard]] double on_mercury() const;
    [[nodiscard]] double on_venus() const;
    [[nodiscard]] double on_earth() const;
    [[nodiscard]] double on_mars() const;
    [[nodiscard]] double on_jupiter() const;
    [[nodiscard]] double on_saturn() const;
    [[nodiscard]] double on_uranus() const;
    [[nodiscard]] double on_neptune() const;

private:
    long long seconds_;
    static constexpr double earth_year_seconds = 31557600.0;
};

}  // namespace space_age

#endif // SPACE_AGE_H
