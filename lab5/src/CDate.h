#include "stdafx.h"

// Месяц
enum class Month {
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay {
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate {
public:
    static char SEPARATOR;

    // инициализируем дату заданными днем, месяцем и годом.
    // примечание: год >= 1970
    CDate(unsigned int day, Month month, unsigned int year);

    // инициализируем дату количеством дней, прошедших после 1 января 1970 года
    // например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
    explicit CDate(unsigned int timestamp);

    // Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
    CDate() = default;

    // возвращает день месяца (от 1 до 31)
    unsigned int GetDay() const;

    // возвращает месяц
    Month GetMonth() const;

    // возвращает год
    unsigned int GetYear() const;

    // возвращает день недели
    WeekDay GetWeekDay() const;

    //Переводит дату на следующий день
    CDate& operator++();

    CDate operator++(int);

    //Переводит дату на предыдущий день
    CDate& operator--();

    CDate operator--(int);

    //Прибавляет к дате заданное целое количество дней. Например:
    //28/02/2010 + 3 = 03/03/2010
    //3 + 28/02/2010 = 03/03/2010
    CDate operator+(int days) const;

    friend CDate operator+(int days, const CDate& cDate);

    //Реализовать 2 версии данного оператора:
    //1.Вычитает из даты заданное количество дней. Например:
    //01/01/2010 - 2 = 30/12/2009
    //2.Находит разность двух дат в днях. Например:
    //01/01/2010 - 30/12/2009 = 3
    //01/01/2010 - 03/01/2010 = -2
    CDate operator-(int days) const;

    int operator-(const CDate& date2) const;

    //<Дата> += <кол-во дней>
    CDate& operator+=(int days);

    //<Дата> -= <кол-во дней>
    CDate& operator-=(int days);

    //TODO реализовать через spaceship <=>
    constexpr auto operator<=>(const CDate& date) const = default;

    //Оператор вывода даты в поток вывода в формате ДД.ММ.ГГГГ, либо INVALID, если дата является недопустимой
    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    //Оператор ввода времени из потока ввода в формате ДД.ММ.ГГГГ, либо INVALID, если дата является недопустимой
    friend std::istream& operator>>(std::istream& is, CDate& date);

private:
    static const int MIN_YEAR = 1970;
    static const unsigned int MAX_YEAR = 9999;

    static const unsigned int MIN_MONTH = 1;
    static const unsigned int MAX_MONTH = 12;

    static const unsigned int MIN_DAY = 1;

    static const unsigned int DAYS_IN_YEAR = 365;
    static constexpr double DAYS_IN_YEAR_EXACT = 365.2425;

    static const unsigned int DAYS_OF_WEEK = 7;
    static const std::map<unsigned int, WeekDay> NUMBER_WEEKDAY_MAP;

    static const std::vector<unsigned int> DAYS_OF_MONTH;

    static const std::vector<unsigned int> DAYS_BEFORE_MONTH;

    static bool IsLeapYear(unsigned int year);

    static bool IsValid(unsigned int day, Month month, unsigned int year);

    unsigned m_days = MIN_DAY;
};