#include "meetup.h"

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : _year{year},
      _month{month} {}

boost::gregorian::date scheduler::find_teenth(boost::date_time::weekdays wd) const
{
    for (std::uint32_t d = 13U; (d <= 19U); ++d) {
        const boost::gregorian::date dt{
            static_cast<int>(_year),
            static_cast<int>(_month),
            static_cast<int>(d)
        };
        if ((dt.day_of_week() == boost::gregorian::greg_weekday(wd))) {
            return dt;
        }
    }
    // Fallback; logically unreachable because there is always exactly one teenth for each weekday
    return boost::gregorian::date{
        static_cast<int>(_year),
        static_cast<int>(_month),
        19
    };
}

boost::gregorian::date scheduler::find_nth(boost::date_time::weekdays wd, std::uint32_t n) const
{
    const boost::gregorian::date first{
        static_cast<int>(_year),
        static_cast<int>(_month),
        1
    };

    const std::int32_t f = static_cast<std::int32_t>(first.day_of_week().as_number());
    const std::int32_t t = static_cast<std::int32_t>(wd);
    const std::int32_t diff_raw = (t - f);
    const std::int32_t diff_mod = static_cast<std::int32_t>(((diff_raw % 7) + 7) % 7);

    const std::uint32_t first_dom = static_cast<std::uint32_t>(1) + static_cast<std::uint32_t>(diff_mod);
    const std::uint32_t day = (first_dom + static_cast<std::uint32_t>(7U * (n - 1U)));

    return boost::gregorian::date{
        static_cast<int>(_year),
        static_cast<int>(_month),
        static_cast<int>(day)
    };
}

boost::gregorian::date scheduler::find_last(boost::date_time::weekdays wd) const
{
    const std::int32_t last_dom = static_cast<std::int32_t>(boost::gregorian::gregorian_calendar::end_of_month_day(
        static_cast<int>(_year),
        static_cast<int>(_month)
    ));

    boost::gregorian::date d{
        static_cast<int>(_year),
        static_cast<int>(_month),
        static_cast<int>(last_dom)
    };

    const boost::gregorian::greg_weekday target{wd};
    while ((d.day_of_week() != target)) {
        d -= boost::gregorian::days{1};
    }
    return d;
}

// Teenths
boost::gregorian::date scheduler::monteenth() const { return find_teenth(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(boost::date_time::Sunday); }

// Mondays
boost::gregorian::date scheduler::first_monday() const { return find_nth(boost::date_time::Monday, 1U); }
boost::gregorian::date scheduler::second_monday() const { return find_nth(boost::date_time::Monday, 2U); }
boost::gregorian::date scheduler::third_monday() const { return find_nth(boost::date_time::Monday, 3U); }
boost::gregorian::date scheduler::fourth_monday() const { return find_nth(boost::date_time::Monday, 4U); }
boost::gregorian::date scheduler::last_monday() const { return find_last(boost::date_time::Monday); }

// Tuesdays
boost::gregorian::date scheduler::first_tuesday() const { return find_nth(boost::date_time::Tuesday, 1U); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth(boost::date_time::Tuesday, 2U); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth(boost::date_time::Tuesday, 3U); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth(boost::date_time::Tuesday, 4U); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last(boost::date_time::Tuesday); }

// Wednesdays
boost::gregorian::date scheduler::first_wednesday() const { return find_nth(boost::date_time::Wednesday, 1U); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth(boost::date_time::Wednesday, 2U); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth(boost::date_time::Wednesday, 3U); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth(boost::date_time::Wednesday, 4U); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last(boost::date_time::Wednesday); }

// Thursdays
boost::gregorian::date scheduler::first_thursday() const { return find_nth(boost::date_time::Thursday, 1U); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth(boost::date_time::Thursday, 2U); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth(boost::date_time::Thursday, 3U); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth(boost::date_time::Thursday, 4U); }
boost::gregorian::date scheduler::last_thursday() const { return find_last(boost::date_time::Thursday); }

// Fridays
boost::gregorian::date scheduler::first_friday() const { return find_nth(boost::date_time::Friday, 1U); }
boost::gregorian::date scheduler::second_friday() const { return find_nth(boost::date_time::Friday, 2U); }
boost::gregorian::date scheduler::third_friday() const { return find_nth(boost::date_time::Friday, 3U); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth(boost::date_time::Friday, 4U); }
boost::gregorian::date scheduler::last_friday() const { return find_last(boost::date_time::Friday); }

// Saturdays
boost::gregorian::date scheduler::first_saturday() const { return find_nth(boost::date_time::Saturday, 1U); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth(boost::date_time::Saturday, 2U); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth(boost::date_time::Saturday, 3U); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth(boost::date_time::Saturday, 4U); }
boost::gregorian::date scheduler::last_saturday() const { return find_last(boost::date_time::Saturday); }

// Sundays
boost::gregorian::date scheduler::first_sunday() const { return find_nth(boost::date_time::Sunday, 1U); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth(boost::date_time::Sunday, 2U); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth(boost::date_time::Sunday, 3U); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth(boost::date_time::Sunday, 4U); }
boost::gregorian::date scheduler::last_sunday() const { return find_last(boost::date_time::Sunday); }

}  // namespace meetup
