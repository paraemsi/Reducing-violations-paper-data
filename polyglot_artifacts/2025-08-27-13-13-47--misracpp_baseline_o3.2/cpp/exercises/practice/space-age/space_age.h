#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
public:
    explicit space_age(long long seconds) : m_seconds{seconds} {}

    [[nodiscard]] long long seconds() const noexcept { return m_seconds; }

    [[nodiscard]] double on_mercury()  const noexcept { return age_on(orbital_period_mercury);  }
    [[nodiscard]] double on_venus()    const noexcept { return age_on(orbital_period_venus);    }
    [[nodiscard]] double on_earth()    const noexcept { return age_on(orbital_period_earth);    }
    [[nodiscard]] double on_mars()     const noexcept { return age_on(orbital_period_mars);     }
    [[nodiscard]] double on_jupiter()  const noexcept { return age_on(orbital_period_jupiter);  }
    [[nodiscard]] double on_saturn()   const noexcept { return age_on(orbital_period_saturn);   }
    [[nodiscard]] double on_uranus()   const noexcept { return age_on(orbital_period_uranus);   }
    [[nodiscard]] double on_neptune()  const noexcept { return age_on(orbital_period_neptune);  }

private:
    long long m_seconds;

    [[nodiscard]] double age_on(double orbital_period) const noexcept {
        return static_cast<double>(m_seconds) / seconds_per_earth_year / orbital_period;
    }

    static constexpr double seconds_per_earth_year   = 31557600.0;
    static constexpr double orbital_period_earth     = 1.0;
    static constexpr double orbital_period_mercury   = 0.2408467;
    static constexpr double orbital_period_venus     = 0.61519726;
    static constexpr double orbital_period_mars      = 1.8808158;
    static constexpr double orbital_period_jupiter   = 11.862615;
    static constexpr double orbital_period_saturn    = 29.447498;
    static constexpr double orbital_period_uranus    = 84.016846;
    static constexpr double orbital_period_neptune   = 164.79132;
};

}  // namespace space_age

#endif // SPACE_AGE_H
