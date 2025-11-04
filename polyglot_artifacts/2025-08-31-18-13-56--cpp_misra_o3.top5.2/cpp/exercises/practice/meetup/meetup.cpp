#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* helper type aliases – kept minimal to avoid unused-alias warnings */

/* ----- ctor ----- */
scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year{year},
      m_month{month}
{
    /* no-op */
}

/* ----- private utilities ----- */
date scheduler::teenth(const boost::gregorian::greg_weekday& wd) const
{
    const std::int32_t yr {m_year};
    const std::int32_t mon {static_cast<std::int32_t>(m_month)};
    for(std::uint8_t d {13U}; d <= 19U; ++d)
    {
        const date candidate {yr, mon, static_cast<std::int32_t>(d)};
        if(candidate.day_of_week() == wd)
        {
            return candidate;
        }
    }
    throw std::logic_error("No teenth day found");
}

date scheduler::nth(const std::uint8_t index, const boost::gregorian::greg_weekday& wd) const
{
    const date first_dom {m_year, static_cast<std::int32_t>(m_month), 1};
    const std::int32_t wd_first {first_dom.day_of_week().as_number()};
    const std::int32_t wd_target {wd.as_number()};

    const std::int32_t diff {(wd_target - wd_first + 7) % 7};

    const std::int32_t day_value {1 + diff + (static_cast<std::int32_t>(index - 1U) * 7)};

    const std::int32_t eom {boost::gregorian::gregorian_calendar::end_of_month_day(
        m_year, static_cast<unsigned short>(m_month))};

    if(day_value > eom)
    {
        throw std::logic_error("Requested nth weekday does not exist in month");
    }

    return date {m_year, static_cast<std::int32_t>(m_month), day_value};
}

date scheduler::last(const boost::gregorian::greg_weekday& wd) const
{
    const std::int32_t eom {boost::gregorian::gregorian_calendar::end_of_month_day(
        m_year, static_cast<unsigned short>(m_month))};

    const date last_dom {m_year, static_cast<std::int32_t>(m_month), eom};
    const std::int32_t diff {(last_dom.day_of_week().as_number() - wd.as_number() + 7) % 7};

    const std::int32_t day_value {eom - diff};

    return date {m_year, static_cast<std::int32_t>(m_month), day_value};
}

/* ----- “teenth” public API ----- */
date scheduler::monteenth()  const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::tuesteenth() const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::wednesteenth()const noexcept{ return teenth(boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::thursteenth()const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::friteenth()  const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::saturteenth()const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::sunteenth()  const noexcept { return teenth(boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

/* ----- first ----- */
date scheduler::first_monday()    const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::first_tuesday()   const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::first_wednesday() const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::first_thursday()  const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::first_friday()    const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::first_saturday()  const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::first_sunday()    const { return nth(1U, boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

/* ----- second ----- */
date scheduler::second_monday()    const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::second_tuesday()   const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::second_wednesday() const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::second_thursday()  const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::second_friday()    const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::second_saturday()  const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::second_sunday()    const { return nth(2U, boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

/* ----- third ----- */
date scheduler::third_monday()    const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::third_tuesday()   const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::third_wednesday() const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::third_thursday()  const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::third_friday()    const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::third_saturday()  const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::third_sunday()    const { return nth(3U, boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

/* ----- fourth ----- */
date scheduler::fourth_monday()    const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::fourth_tuesday()   const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::fourth_wednesday() const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::fourth_thursday()  const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::fourth_friday()    const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::fourth_saturday()  const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::fourth_sunday()    const { return nth(4U, boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

/* ----- last ----- */
date scheduler::last_monday()    const { return last(boost::gregorian::greg_weekday{boost::date_time::Monday});    }
date scheduler::last_tuesday()   const { return last(boost::gregorian::greg_weekday{boost::date_time::Tuesday});   }
date scheduler::last_wednesday() const { return last(boost::gregorian::greg_weekday{boost::date_time::Wednesday}); }
date scheduler::last_thursday()  const { return last(boost::gregorian::greg_weekday{boost::date_time::Thursday});  }
date scheduler::last_friday()    const { return last(boost::gregorian::greg_weekday{boost::date_time::Friday});    }
date scheduler::last_saturday()  const { return last(boost::gregorian::greg_weekday{boost::date_time::Saturday});  }
date scheduler::last_sunday()    const { return last(boost::gregorian::greg_weekday{boost::date_time::Sunday});    }

}  // namespace meetup
