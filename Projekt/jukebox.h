#ifndef JUKEBOX_H
#define JUKEBOX_H
#include <vector>
#include "menu.h"
#include "album.h"

const std::string OUTFILE ="uttest.txt";
const std::string INFILE = "jukebox.txt";

class Jukebox
{
    private:
        std::vector<Album> albvec;
        Menu menu;

        // File-menyn
        void fileMenu(Menu &menu);
        void openFromFile();
        void saveToFile();

        // Medlemsfunktioner
        void addAlbum();
        int findAlbumIdx(std::string &key);
        void delAlbum();
        void printAlbumFormatted(unsigned int &idx);
        void printAlbumVector();

        // Print-menyn
        void printMenu();
        void printAlbum();
        void printAlbumsByTitle();
        void printAlbumsByDuration();
        void printAlbumTitles();
        void printAlbumDurations();

        // Play-menyn
        //void playMenu();
    public:
        Jukebox();
        int run();
};

#endif // JUKEBOX_H
