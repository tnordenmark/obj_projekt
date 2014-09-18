#include <iostream>
#include <iomanip>
#include "mytime.h"
using namespace std;

// Konstruktorer
Time::Time()
{
    hour = 0;
    min = 0;
    sec = 0;
}

Time::Time(int pHour, int pMin, int pSec)
{
    hour = pHour;
    min = pMin;
    sec = pSec;
}

// Setters
void Time::setHour(int pHour)
{
    hour = pHour;
}

void Time::setMinute(int pMin)
{
    min = pMin;
}

void Time::setSecond(int pSec)
{
    sec = pSec;
}

// Överlagring av + operatorn med hjälp av += operatorn
Time Time::operator+(const Time &t) const
{
    Time sum = *this;
    sum += t;

    return sum;
}

// Överlagring av < operatorn för att jämföra två Time-objekt
bool Time::operator<(const Time &t) const
{
    return ((hour * 3600) + (min * 60) + sec) < ((t.hour * 3600) + (t.min * 60) + t.sec);
}

// Överlagring av > operatorn för att jämföra två Time-objekt
bool Time::operator>(const Time &t) const
{
    return ((hour * 3600) + (min * 60) + sec) > ((t.hour * 3600) + (t.min * 60) + t.sec);
}

// Överlagring av == operatorn för att jämföra två Time-objekt
bool Time::operator==(const Time &t) const
{
    return sec == t.sec && min == t.min && hour == t.hour;
}

// Överlagring av += operator för att summera Time-objekt
Time &Time::operator+=(const Time &time)
{
    sec = sec + time.sec;
    min = min + time.min + sec / 60;
    hour = hour + time.hour + min / 60;
    sec %= 60;
    min %= 60;

    return *this;
}

// Överlagring av << operatorn för utskrift av Time-objekt
ostream &operator<<(ostream &os, const Time &t)
{
    os << t.getSecond() + (t.getMinute() * 60) + (t.getHour() * 3600);

    return os;
}

// Överlagring av >> operatorn för inläsning av Time-objekt
istream &operator>>(istream &is, Time &t)
{
    int duration;
    is >> duration;

    t.setHour((duration / 3600) % 60);
    t.setMinute((duration / 60) % 60);
    t.setSecond(duration % 60);

    return is;
}

// Hjälpfunktion för att skriva ut ett Time-objekt
void printTime(const Time &t)
{
    // Om timme är 0 eller mindre
    if(t.getHour() <= 0)
        cout << t.getMinute() << ":" << t.getSecond();
    // Om timme är 1 eller större
    else
        cout << t.getHour() << ":" << t.getMinute() << ":" << t.getSecond();
}
