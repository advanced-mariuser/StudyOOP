#include "catch2/catch_test_macros.hpp"
#include <sstream>
#include "../src/CDate.h"

const unsigned DAYS_IN_YEAR = 365;
const unsigned MIN_YEAR = 1970;
const unsigned MIN_DAY = 1;
const unsigned DAYS_FIRST_LEAP_YEAR = DAYS_IN_YEAR + DAYS_IN_YEAR + 31 + 28;

TEST_CASE("Create default constr success")
{
    CDate cDate;
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp default constr success")
{
    unsigned timestamp = 0;

    auto cDate = CDate(timestamp);
    unsigned expectedDay = MIN_DAY + timestamp;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp days constr success")
{
    unsigned timestamp = 1;

    auto cDate = CDate(timestamp);
    unsigned expectedDay = MIN_DAY + timestamp;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Weekday Success")
{
    CDate cDate = CDate(25, Month::APRIL, 2024);
    CDate cDate1 = CDate(25, Month::APRIL, 2023);

    REQUIRE(-366 == cDate1 - cDate);
    REQUIRE(WeekDay::THURSDAY == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp days above threshold month constr success")
{
    unsigned timestamp = 31;

    auto cDate = CDate(timestamp);
    unsigned expectedDay = 1;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SUNDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp days leap year constr success")
{
    unsigned timestamp = DAYS_FIRST_LEAP_YEAR;

    auto cDate = CDate(timestamp);
    unsigned expectedDay = 29;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = 1972;
    WeekDay expectedWeekDay = WeekDay::TUESDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp days february constr success")
{
    unsigned timestamp = 58;

    auto cDate = CDate(timestamp);
    unsigned expectedDay = 28;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create timestamp days february constr success2")
{
    unsigned expectedDay = 18;
    Month expectedMonth = Month::MAY;
    unsigned expectedYear = 2400;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(expectedDay, expectedMonth, expectedYear);

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create date calendar constr success")
{
    unsigned expectedDay = 28;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(expectedDay, expectedMonth, expectedYear);

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Create leap year calendar constr success")
{
    unsigned expectedDay = 29;
    Month expectedMonth = Month::FEBRUARY;
    int expectedYear = 1972;
    WeekDay expectedWeekDay = WeekDay::TUESDAY;

    CDate cDate = CDate(expectedDay, expectedMonth, expectedYear);

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Invalid date by timestamp days constr failed")
{
    REQUIRE_THROWS_AS(CDate(3999999999), std::invalid_argument);
}

TEST_CASE("Invalid date by year failed")
{
    REQUIRE_THROWS_AS(CDate(10, Month::FEBRUARY, 10000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(10, Month::FEBRUARY, 1969), std::invalid_argument);
}

TEST_CASE("Invalid date by day failed")
{
    REQUIRE_THROWS_AS(CDate(-1, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(0, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(30, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);
}

TEST_CASE("Invalid date by month failed")
{
    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(13), MIN_YEAR), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(0), MIN_YEAR), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(99), MIN_YEAR), std::invalid_argument);
}

TEST_CASE("Plus prefix success")
{
    unsigned expectedDay = MIN_DAY + 1;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    ++cDate;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Plus postfix success")
{
    unsigned expectedDay = MIN_DAY + 1;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    cDate++;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Minus prefix success")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 1, expectedMonth, expectedYear);
    --cDate;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Minus postfix success")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 1, expectedMonth, expectedYear);
    cDate--;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Plus days success")
{
    unsigned expectedDay = MIN_DAY + 2;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    CDate cDate1 = cDate + 2;
    REQUIRE(expectedDay == cDate1.GetDay());
    REQUIRE(expectedMonth == cDate1.GetMonth());
    REQUIRE(expectedYear == cDate1.GetYear());
    REQUIRE(expectedWeekDay == cDate1.GetWeekDay());

    CDate cDate2 = 2 + cDate;
    REQUIRE(expectedDay == cDate2.GetDay());
    REQUIRE(expectedMonth == cDate2.GetMonth());
    REQUIRE(expectedYear == cDate2.GetYear());
    REQUIRE(expectedWeekDay == cDate2.GetWeekDay());

    CDate cDate3 = cDate + 0;
    REQUIRE(cDate.GetDay() == cDate3.GetDay());
    REQUIRE(cDate.GetMonth() == cDate3.GetMonth());
    REQUIRE(cDate.GetYear() == cDate3.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate3.GetWeekDay());

    CDate cDate4 = cDate - 0;
    REQUIRE(cDate.GetDay() == cDate4.GetDay());
    REQUIRE(cDate.GetMonth() == cDate4.GetMonth());
    REQUIRE(cDate.GetYear() == cDate4.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate4.GetWeekDay());
}

TEST_CASE("Minus days success")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = cDate - 2;
    REQUIRE(expectedDay == cDate1.GetDay());
    REQUIRE(expectedMonth == cDate1.GetMonth());
    REQUIRE(expectedYear == cDate1.GetYear());
    REQUIRE(expectedWeekDay == cDate1.GetWeekDay());

    CDate cDate2 = cDate - 0;
    REQUIRE(cDate.GetDay() == cDate2.GetDay());
    REQUIRE(cDate.GetMonth() == cDate2.GetMonth());
    REQUIRE(cDate.GetYear() == cDate2.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate2.GetWeekDay());
}

TEST_CASE("Minus dates success")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 1, expectedMonth, expectedYear);
    unsigned resultDays = cDate - cDate2;
    REQUIRE(expectedDay == resultDays);

    resultDays = cDate2 - cDate;
    REQUIRE(-expectedDay == resultDays);
}

TEST_CASE("Plus equals success")
{
    unsigned expectedDay = MIN_DAY + 2;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    cDate += 2;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Minus equals success")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    cDate -= 2;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("Equals success")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);

    REQUIRE(cDate == cDate1);
    REQUIRE_FALSE(cDate1 == cDate2);
}

TEST_CASE("More success")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);

    REQUIRE(cDate < cDate1);
    REQUIRE_FALSE(cDate1 < cDate);
}

TEST_CASE("Less success")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);

    REQUIRE_FALSE(cDate > cDate1);
    REQUIRE(cDate1 > cDate);
}

TEST_CASE("More equals success")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);

    REQUIRE(cDate <= cDate1);
    REQUIRE_FALSE(cDate1 <= cDate);
    REQUIRE(cDate1 <= cDate2);
}

TEST_CASE("Less equals success")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 3, expectedMonth, expectedYear);

    REQUIRE_FALSE(cDate >= cDate1);
    REQUIRE(cDate1 >= cDate);
    REQUIRE(cDate1 >= cDate2);
}

TEST_CASE("Ostream success")
{
    CDate date(15, Month::MARCH, 2023);
    std::ostringstream oss;
    oss << date;

    REQUIRE("15.3.2023" == oss.str());
}

TEST_CASE("Istream success")
{
    std::istringstream iss("25.12.2022");
    CDate date;
    iss >> date;
    REQUIRE(25 == date.GetDay());
    REQUIRE(Month::DECEMBER == date.GetMonth());
    REQUIRE(2022 == date.GetYear());
    REQUIRE_FALSE(iss.bad());
}

TEST_CASE("Istream failed")
{
    std::istringstream iss("25.12?2022");
    CDate date;
    iss >> date;
    REQUIRE(iss.bad());
}
