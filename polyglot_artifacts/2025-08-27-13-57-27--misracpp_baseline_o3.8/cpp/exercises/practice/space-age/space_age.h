#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
public:
    explicit space_age(long long seconds);

    long long seconds() const;

    double on_mercury() const;
    double on_venus() const;
    double on_earth() const;
    double on_mars() const;
    double on_jupiter() const;
    double on_saturn() const;
    double on_uranus() const;
    double on_neptune() const;

private:
    long long seconds_;
    static constexpr double earth_year_in_seconds = 31557600.0;

    // Compute age on a planet given its orbital period in Earth years
    double age_on_planet(double orbital_period_in_earth_years) const;
};

}  // namespace space_age

#endif // SPACE_AGE_H
