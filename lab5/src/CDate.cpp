#include "CDate.h"

using namespace std;

const vector<unsigned int> CDate::DAYS_BEFORE_MONTH = {
        0,
        31,
        59,
        90,
        120,
        151,
        181,
        212,
        243,
        273,
        304,
        334,
};

const vector<unsigned int> CDate::DAYS_OF_MONTH = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31,
};

//TODO почему среда 0
//TODO потому что 01.01.1970 это среда
const map<unsigned int, WeekDay> CDate::NUMBER_WEEKDAY_MAP = {
        {1, WeekDay::THURSDAY},
        {2, WeekDay::FRIDAY},
        {3, WeekDay::SATURDAY},
        {4, WeekDay::SUNDAY},
        {5, WeekDay::MONDAY},
        {6, WeekDay::TUESDAY},
        {0, WeekDay::WEDNESDAY}
};

char CDate::SEPARATOR = '.';

CDate::CDate(unsigned int day, Month month, unsigned int year)
{
    if (!IsValid(day, month, year))
    {
        throw invalid_argument("Invalid CDate");
    }

    m_days += day - MIN_DAY;
    m_days += DAYS_BEFORE_MONTH.at(static_cast<int>(month) - 1);

    //TODO избавился от цикла
    unsigned int yearsSinceMin = year - MIN_YEAR;
    //вычислили количество дней, прошедших с минимального года до текущего года, с учетом високосных лет
    unsigned int leapYearsSinceMin = (yearsSinceMin / 4) - (yearsSinceMin / 100) + (yearsSinceMin / 400);
    unsigned int daysSinceMinYear = yearsSinceMin * DAYS_IN_YEAR + leapYearsSinceMin;

    if (IsLeapYear(year) && month > Month::FEBRUARY)
    {
        daysSinceMinYear += 1;
    }

    m_days += daysSinceMinYear;
}

CDate::CDate(unsigned int timestamp)
{
    m_days += timestamp;

    if (GetYear() < MIN_YEAR || GetYear() > MAX_YEAR)
    {
        throw invalid_argument("Invalid CDate");
    }
}

unsigned int CDate::GetDay() const
{
    unsigned int year = MIN_YEAR + m_days / DAYS_IN_YEAR_EXACT;
    //количества дней, прошедших с начала текущего года:
    unsigned int days = m_days - static_cast<int>((year - MIN_YEAR) * DAYS_IN_YEAR + (year - MIN_YEAR) / 4 -
                                                  (year - MIN_YEAR) / 100 + (year - MIN_YEAR) / 400);

    //TODO цикл в рамках одного года
    for (size_t index = 0; index < DAYS_OF_MONTH.size(); ++index)
    {
        int daysOfMonth = DAYS_OF_MONTH[index];
        if (index == static_cast<int>(Month::FEBRUARY) - 1)
        {
            daysOfMonth += IsLeapYear(year);
        }
        if (days <= daysOfMonth)
        {
            break;
        }
        days -= daysOfMonth;
    }
    return days;
}

Month CDate::GetMonth() const
{
    unsigned int year = MIN_YEAR + m_days / DAYS_IN_YEAR_EXACT;
    unsigned int days = m_days - static_cast<int>((year - MIN_YEAR) * DAYS_IN_YEAR + (year - MIN_YEAR) / 4 -
                                                  (year - MIN_YEAR) / 100 + (year - MIN_YEAR) / 400);

    //цикл в рамках одного года
    for (size_t index = 0; index < DAYS_OF_MONTH.size(); ++index)
    {
        int daysOfMonth = DAYS_OF_MONTH[index];
        if (index == static_cast<int>(Month::FEBRUARY) - 1)
        {
            daysOfMonth += IsLeapYear(year);
        }
        if (days <= daysOfMonth)
        {
            return static_cast<Month>(index + 1);
        }
        days -= daysOfMonth;
    }

    return Month::DECEMBER;
}


unsigned int CDate::GetYear() const
{
    unsigned int year = MIN_YEAR;
    unsigned int days = m_days;

    year = static_cast<unsigned int>(year + days / DAYS_IN_YEAR_EXACT);
    return year;
}

WeekDay CDate::GetWeekDay() const
{
    return NUMBER_WEEKDAY_MAP.at(m_days % DAYS_OF_WEEK);
}

//Префиксный инкремент
CDate &CDate::operator++()
{
    ++m_days;
    return *this;
}

//Постфиксный инкремент
CDate CDate::operator++(int)
{
    CDate temp(*this);
    ++(*this);
    return temp;
}

//Префиксный декремент
CDate &CDate::operator--()
{
    --m_days;
    return *this;
}

//Постфиксный декремент
CDate CDate::operator--(int)
{
    CDate temp(*this);
    --(*this);
    return temp;
}

CDate CDate::operator+(int days) const
{
    return CDate(m_days + days - MIN_DAY);
}

CDate operator+(int days, const CDate &cDate)
{
    return CDate(cDate.m_days + days - CDate::MIN_DAY);
}

CDate CDate::operator-(int days) const
{
    return CDate(m_days - days - MIN_DAY);
}

int CDate::operator-(const CDate &date2) const
{
    auto deltaDays = static_cast<int>(m_days) - static_cast<int>(date2.m_days);

    return deltaDays;
}

CDate &CDate::operator+=(int days)
{
    m_days += static_cast<unsigned int>(days);
    return *this;
}

CDate &CDate::operator-=(int days)
{
    m_days -= static_cast<unsigned int>(days);
    return *this;
}

ostream &operator<<(ostream &os, const CDate &date)
{
    os << date.GetDay() << CDate::SEPARATOR << static_cast<int>(date.GetMonth()) << CDate::SEPARATOR << date.GetYear();
    return os;
}

istream &operator>>(istream &is, CDate &date)
{
    unsigned int day;
    unsigned year;
    int month;
    char dot;
    is >> day >> dot >> month >> dot >> year;
    if (dot != CDate::SEPARATOR)
    {
        is.setstate(ios::badbit);
    }

    date = CDate(day, static_cast<Month>(month), year);
    return is;
}

bool CDate::IsLeapYear(unsigned int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool CDate::IsValid(unsigned int day, Month month, unsigned int year)
{
    bool isValidMonth = static_cast<int>(month) >= MIN_MONTH && static_cast<int>(month) <= MAX_MONTH;

    bool isValidDay = false;
    if (isValidMonth)
    {
        isValidDay = MIN_DAY <= day && day <= DAYS_OF_MONTH.at(static_cast<int>(month) - 1) + IsLeapYear(year);
    }

    bool isValidYear = MIN_YEAR <= year && year <= MAX_YEAR;

    return isValidYear && isValidMonth && isValidDay;
}