#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include <vector>
#include "song.h"

class Album
{
    private:
        std::string album_title;
        std::vector<Song> songvec;
    public:
        Album();
        Album(std::string pAlbum);

        // Setters
        void setAlbum(std::string pAlbum);

        // Getters
        std::string getAlbum() const {return album_title;}
        std::vector<Song> getSongvec() const {return songvec;}

        // Medlemsfunktioner
        void addSong(Song &song);
        int getNrSongs() const;
        Time getAlbumDuration() const;
        void clearSongvec();

        // Överlagrade operatorer
        bool operator<(const Album &album) const;
        bool operator>(const Album &album) const;
};

// Överlagring av operatorer för utskrift och inläsning
std::ostream &operator<<(std::ostream &os, const Album &album);
std::istream &operator>>(std::istream &is, Album &album);

#endif // ALBUM_H
