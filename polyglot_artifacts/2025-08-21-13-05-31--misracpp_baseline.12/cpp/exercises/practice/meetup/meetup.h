#ifndef MEETUP_H
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

class scheduler {
public:
    scheduler(boost::gregorian::greg_month month, int year)
        : m_year(year), m_month(month.as_number()) {}

    boost::gregorian::date monteenth()    const { return teenth(boost::date_time::Monday);    }
    boost::gregorian::date tuesteenth()   const { return teenth(boost::date_time::Tuesday);   }
    boost::gregorian::date wednesteenth() const { return teenth(boost::date_time::Wednesday); }
    boost::gregorian::date thursteenth()  const { return teenth(boost::date_time::Thursday);  }
    boost::gregorian::date friteenth()    const { return teenth(boost::date_time::Friday);    }
    boost::gregorian::date saturteenth()  const { return teenth(boost::date_time::Saturday);  }
    boost::gregorian::date sunteenth()    const { return teenth(boost::date_time::Sunday);    }

    boost::gregorian::date first_monday()    const { return nth_weekday(1, boost::date_time::Monday);    }
    boost::gregorian::date first_tuesday()   const { return nth_weekday(1, boost::date_time::Tuesday);   }
    boost::gregorian::date first_wednesday() const { return nth_weekday(1, boost::date_time::Wednesday); }
    boost::gregorian::date first_thursday()  const { return nth_weekday(1, boost::date_time::Thursday);  }
    boost::gregorian::date first_friday()    const { return nth_weekday(1, boost::date_time::Friday);    }
    boost::gregorian::date first_saturday()  const { return nth_weekday(1, boost::date_time::Saturday);  }
    boost::gregorian::date first_sunday()    const { return nth_weekday(1, boost::date_time::Sunday);    }

    boost::gregorian::date second_monday()    const { return nth_weekday(2, boost::date_time::Monday);    }
    boost::gregorian::date second_tuesday()   const { return nth_weekday(2, boost::date_time::Tuesday);   }
    boost::gregorian::date second_wednesday() const { return nth_weekday(2, boost::date_time::Wednesday); }
    boost::gregorian::date second_thursday()  const { return nth_weekday(2, boost::date_time::Thursday);  }
    boost::gregorian::date second_friday()    const { return nth_weekday(2, boost::date_time::Friday);    }
    boost::gregorian::date second_saturday()  const { return nth_weekday(2, boost::date_time::Saturday);  }
    boost::gregorian::date second_sunday()    const { return nth_weekday(2, boost::date_time::Sunday);    }

    boost::gregorian::date third_monday()    const { return nth_weekday(3, boost::date_time::Monday);    }
    boost::gregorian::date third_tuesday()   const { return nth_weekday(3, boost::date_time::Tuesday);   }
    boost::gregorian::date third_wednesday() const { return nth_weekday(3, boost::date_time::Wednesday); }
    boost::gregorian::date third_thursday()  const { return nth_weekday(3, boost::date_time::Thursday);  }
    boost::gregorian::date third_friday()    const { return nth_weekday(3, boost::date_time::Friday);    }
    boost::gregorian::date third_saturday()  const { return nth_weekday(3, boost::date_time::Saturday);  }
    boost::gregorian::date third_sunday()    const { return nth_weekday(3, boost::date_time::Sunday);    }

    boost::gregorian::date fourth_monday()    const { return nth_weekday(4, boost::date_time::Monday);    }
    boost::gregorian::date fourth_tuesday()   const { return nth_weekday(4, boost::date_time::Tuesday);   }
    boost::gregorian::date fourth_wednesday() const { return nth_weekday(4, boost::date_time::Wednesday); }
    boost::gregorian::date fourth_thursday()  const { return nth_weekday(4, boost::date_time::Thursday);  }
    boost::gregorian::date fourth_friday()    const { return nth_weekday(4, boost::date_time::Friday);    }
    boost::gregorian::date fourth_saturday()  const { return nth_weekday(4, boost::date_time::Saturday);  }
    boost::gregorian::date fourth_sunday()    const { return nth_weekday(4, boost::date_time::Sunday);    }

    boost::gregorian::date last_monday()    const { return last_weekday(boost::date_time::Monday);    }
    boost::gregorian::date last_tuesday()   const { return last_weekday(boost::date_time::Tuesday);   }
    boost::gregorian::date last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
    boost::gregorian::date last_thursday()  const { return last_weekday(boost::date_time::Thursday);  }
    boost::gregorian::date last_friday()    const { return last_weekday(boost::date_time::Friday);    }
    boost::gregorian::date last_saturday()  const { return last_weekday(boost::date_time::Saturday);  }
    boost::gregorian::date last_sunday()    const { return last_weekday(boost::date_time::Sunday);    }

private:
    int m_year;
    unsigned short m_month;

    boost::gregorian::date teenth(boost::date_time::weekdays wd) const {
        for (int d = 13; d <= 19; ++d) {
            boost::gregorian::date date(m_year, boost::gregorian::greg_month(m_month), d);
            if (date.day_of_week() == wd)
                return date;
        }
        throw std::logic_error("No teenth weekday found");
    }

    boost::gregorian::date nth_weekday(int n, boost::date_time::weekdays wd) const {
        boost::gregorian::date first(m_year, boost::gregorian::greg_month(m_month), 1);
        int first_wd = first.day_of_week();
        int offset = (static_cast<int>(wd) - first_wd + 7) % 7;
        int day = 1 + offset + 7 * (n - 1);
        boost::gregorian::date result(m_year, boost::gregorian::greg_month(m_month), day);
        if (result.month().as_number() != m_month)
            throw std::logic_error("No such weekday in this month");
        return result;
    }

    boost::gregorian::date last_weekday(boost::date_time::weekdays wd) const {
        boost::gregorian::date d(m_year, boost::gregorian::greg_month(m_month), 1);
        d += boost::gregorian::months(1);
        d -= boost::gregorian::days(1); // last day of month
        int last_wd = d.day_of_week();
        int offset = (last_wd - static_cast<int>(wd) + 7) % 7;
        boost::gregorian::date result = d - boost::gregorian::days(offset);
        return result;
    }
};

}  // namespace meetup

#endif // MEETUP_H
