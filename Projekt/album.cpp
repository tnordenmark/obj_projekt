#include <sstream>
#include "album.h"
using namespace std;

Album::Album()
{
    album_title = "";
}

Album::Album(string pAlbum)
{
    album_title = pAlbum;
}

// Setters
void Album::setAlbum(string pAlbum)
{
    album_title = pAlbum;
}

// Lägg till en låt till ett album
void Album::addSong(Song &song)
{
    // Lägg ett Song-objekt i vectorn
    songvec.push_back(song);
}

// Hjälpfunktion för att hämta antalet låtar i album-vectorn
int Album::getNrSongs() const
{
    // Returnera vectorns storlek, dvs antal låtar
    return songvec.size();
}

// Hjälpfunktion för att hämta ett albums totaltid i sekunder
Time Album::getAlbumDuration() const
{
    // Skapa Time-objekt
    Time sum;

    // Stega igenom vectorn och addera varje låts tid till totaltiden i sum
    for(auto i: songvec)
        sum += i.getDuration();

    // Returnera Time-objektet sum
    return sum;
}

// Nollställ låtvectorn
void Album::clearSongvec()
{
    songvec.clear();
}

// Överlagring av < operator för att jämföra albums totallängd
bool Album::operator<(const Album &album) const
{
    return getAlbumDuration() < album.getAlbumDuration();
}

// Överlagring av > operator för att jämföra albums totallängd
bool Album::operator>(const Album &album) const
{
    return getAlbumDuration() > album.getAlbumDuration();
}

// Avgränsare för utskrift och inläsning från fil
const char DELIM = '|';

// Överlagring av << operator för utskrift av album
ostream &operator<<(ostream &os, const Album &album)
{
    // Skriv ut albumtitel
    os << album.getAlbum() << endl;
    // Skriv ut antal låtar
    os << album.getNrSongs() << endl;
    // Skriv ut samtliga låtar i albumets vector
    for(int i = 0, j = 1; i < album.getNrSongs(); i++, j++)
    {
        os << album.getSongvec()[i];
        // Newline varje rad utom sista låten i varje album
        if(j % album.getNrSongs() != 0)
            os << endl;
    }

    return os;
}

// Överlagring av >> operator för inläsning av album
istream &operator>>(istream &is, Album &album)
{
    // Skapa Song-objekt
    Song s;
    // Temporär sträng för att lagra input
    string str;

    // Om låtvectorn innehåller en föregående låtlista
    if(!album.getSongvec().empty())
        // Nollställ låtvectorn
        album.clearSongvec();

    // Läs in albumets namn
    getline(is, str);
    // Sätt albumets datamedlem till inläst namn
    album.setAlbum(str);

    // Integer för att lagra antal låtar
    int num_songs = 0;
    // Läs in antal låtar per album
    getline(is, str);
    // Strängström av inläst sträng med antal låtar
    stringstream numstream(str);
    // Omvandla inläst antal låtar till integer
    numstream >> num_songs;

    // Läs in rätt antal låtar
    for(int i = 0; i < num_songs; ++i)
    {
        // Lägg till låtar i albumets vector
        is >> s;
        // Läs bort newline
        is.ignore(10000, '\n');
        album.addSong(s);
    }

    return is;
}
