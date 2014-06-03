#include "song.h"
using namespace std;

// Konstruktorer
Song::Song()
{
    title = "";
    artist = "";
}

Song::Song(string pTitle, string pArtist, Time pDuration)
{
    title = pTitle;
    artist = pArtist;
    duration = pDuration;
}

// Setters
void Song::setTitle(string pTitle)
{
    title = pTitle;
}

void Song::setArtist(string pArtist)
{
    artist = pArtist;
}

void Song::setDuration(Time pDuration)
{
    duration = pDuration;
}

// Avgränsare för utskrift och inläsning från fil
const char DELIM = '|';

// Överlagring av << operator för utskrift av låt
ostream &operator<<(ostream &os, const Song &song)
{
    os << song.getTitle() << DELIM << song.getArtist() << DELIM << song.getDuration();

    return os;
}

// Överlagring av >> operator för inläsning av låt
istream &operator>>(istream &is, Song &song)
{
    Time t;
    string str;

    getline(is, str, DELIM);
    song.setTitle(str);

    getline(is, str, DELIM);
    song.setArtist(str);

    is >> t;
    song.setDuration(t);

    return is;
}
