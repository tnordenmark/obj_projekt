#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <string>
#include "mytime.h"

class Song
{
    private:
        std::string title;
        std::string artist;
        Time duration;
    public:
        // Konstruktorer
        Song();
        Song(std::string pTitle, std::string pArtist, Time pDuration);

        // Setters
        void setTitle(std::string pTitle);
        void setArtist(std::string pArtist);
        void setDuration(Time pDuration);

        // Getters inline
        std::string getTitle() const {return title;}
        std::string getArtist() const {return artist;}
        Time getDuration() const {return duration;}
};

// Överlagring av operatorer för utskrift och inläsning
std::ostream &operator<<(std::ostream &os, const Song &song);
std::istream &operator>>(std::istream &is, Song &song);

#endif // SONG_H
