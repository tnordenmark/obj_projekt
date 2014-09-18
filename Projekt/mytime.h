#ifndef MYTIME_H
#define MYTIME_H

class Time
{
    private:
        int hour;
        int min;
        int sec;
    public:
        // Konstruktorer
        Time();
        Time(int pHour, int pMin, int pSec);

        // Setters
        void setHour(int pHour);
        void setMinute(int pMin);
        void setSecond(int pSec);

        //Getters inline
        int getHour() const {return hour;}
        int getMinute() const {return min;}
        int getSecond() const {return sec;}

        // Överlagrade operatorer
        Time operator+(const Time &t) const;
        bool operator<(const Time &t) const;
        bool operator>(const Time &t) const;
        bool operator==(const Time &t) const;
        Time &operator+=(const Time &time);

};
// Utskrift av ett Time-objekt
void printTime(Time const &t);

// Överlagring av operatorer för utskrift och inläsning
std::ostream &operator<<(std::ostream &os, const Time &t);
std::istream &operator>>(std::istream &is, Time &t);

#endif // MYTIME_H
