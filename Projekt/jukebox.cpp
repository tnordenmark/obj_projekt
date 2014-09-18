#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "jukebox.h"
#include "jukefunc.h"
using namespace std;

//------------------------------------------------------------------------------
// fileMenu
//------------------------------------------------------------------------------
// Uppgift: Undermenyn File
// Indata : -
// Utdata : -
//------------------------------------------------------------------------------
void Jukebox::fileMenu(Menu &menu)
{
    // Skapa objekt för huvudmenyn
    Menu fileMenu;
    // Integer för antal val i menyn
    int menumax = 0;

    // Statisk bool för att hålla koll på om alternativet Open redan körts
    // eller inte, detta för att menyalternativen ska vara enabled vid ett
    // andra besök i filemenyn
    static bool ranOpen = true;

    // Om menyn skapas för första gången
    if(ranOpen)
    {
        // Lägg till några menyalternativ och uppdatera
        // räknaren för antal menyalternativ
        fileMenu.addItem("Open...", true); // 1
        menumax++;
        fileMenu.addItem("Save...", false); // 2
        menumax++;
        fileMenu.addItem("Back to main menu", true); // 3
        menumax++;
    }
    // Om Open körts en gång
    else
    {
        fileMenu.addItem("Open...", true); // 1
        menumax++;
        fileMenu.addItem("Save...", true); // 2
        menumax++;
        fileMenu.addItem("Back to main menu", true); // 3
        menumax++;
    }

    // Kör menyn igen?
    bool again = true;

    // Loop för Filemenyn
    do
    {
        // Skriv ut menyalternativen
        fileMenu.printMenuItems();

        // Hantera de olika valen
        switch(fileMenu.getMenuChoice(menumax))
        {
            // Open
            case 1:
                // Om menyvalets enableflagga är true
                if(fileMenu.getMenuvec()[0].getEnabled())
                {
                    // Anropa funktionen
                    openFromFile();
                    // Sätt ranOpen till false så att Save stannar enabled
                    // även efter ett besök i huvudmenyn
                    ranOpen = false;
                    // Sätt disabled menyer till enabled
                    fileMenu.getMenuvec()[1].setEnabled(true);
                    menu.getMenuvec()[1].setEnabled(true);
                    menu.getMenuvec()[2].setEnabled(true);
                    menu.getMenuvec()[3].setEnabled(true);
                }
                // Annars felmeddelande
                else
                    cout << "Open is disabled..." << endl;
                break;
            // Save
            case 2:
                // Om menyvalets enableflagga är true
                if(fileMenu.getMenuvec()[1].getEnabled())
                    // Anropa funktionen
                    saveToFile();
                // Annars felmeddelande
                else
                    cout << "Save is disabled..." << endl;
                break;
            // Back to main menu
            case 3:
                // Om menyvalets enableflagga är true
                if(fileMenu.getMenuvec()[2].getEnabled())
                {
                    // Avbryt loopen och återgå till huuvdmenyn
                    again = false;
                }
                // Annars felmeddelande
                else
                    cout << "Back to main menu is disabled..." << endl;
                break;
        }
    }while(again);
}
//------------------------------------------------------------------------------
// openFromFile
//------------------------------------------------------------------------------
// Uppgift: File -> Open, läs spellista från fil
// Indata : -
// Utdata : -
//------------------------------------------------------------------------------
void Jukebox::openFromFile()
{
    // Skapa infilobjekt
    fstream inFile(INFILE, ios::in);
    // Skapa albumobjekt
    Album a;

    // Om vectorn (listan) inte är tom
    if(!albvec.empty())
        // Rensa vectorn
        albvec.clear();

    // Om filen är öppen
    if(inFile.is_open())
        // Så länge det finns data att läsa
        while(inFile >> a)
            albvec.push_back(a);
    else
        cout << "I/O error, could not open file.";

    // Stäng infilen
    inFile.close();
}
//------------------------------------------------------------------------------
// saveToFile
//------------------------------------------------------------------------------
// Uppgift: File -> Save, skriver spellista till fil
// Indata : -
// Utdata : -
//------------------------------------------------------------------------------
void Jukebox::saveToFile()
{
    // Skapa utfilobjekt
    fstream outFile(OUTFILE, ios::out);

    // Om utfilen är öppen
    if(outFile.is_open())
    {
        // Stega igenom vectorn
        for(auto i: albvec)
            // Och skriv varje objekt till utfilen
            outFile << i << endl;
    }
    else
        // Felmeddelande om filen ej kunde öppnas
        cout << "I/O error, could not open file.";

    // Stäng utfilen
    outFile.close();
}
//------------------------------------------------------------------------------
// addAlbum
//------------------------------------------------------------------------------
// Uppgift: Lägger till ett album i spellistan
// Indata : -
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::addAlbum()
{
    // Skapa de objekt som behövs
    Time t;
    Song s;
    Album a;

    // Variabler för inmatad data
    string str;
    int time = 0;
    char yesno;

    // Läs bort huvudmenyns newline
    cin.get();

    // Mata in albumtitel
    cout << "Album title: ";
    getline(cin, str);
    a.setAlbum(str);

    cout << "Input songs:" << endl;

    // Loop för att lägga till låtar på albumet
    do
    {
        cout << "Title: ";
        getline(cin, str);
        s.setTitle(str);

        cout << "Artist: ";
        getline(cin, str);
        s.setArtist(str);

        cout << "Duration (hour): ";
        cin >> time;
        t.setHour(time);

        cout << "Duration (min): ";
        cin >> time;
        t.setMinute(time);

        cout << "Duration (sec): ";
        cin >> time;
        t.setSecond(time);

        s.setDuration(t);
        a.addSong(s);

        // Fråga om en låt till ska läggas till
        do
        {
            yesno = yesNoMenu();
            cin.get();
        }while(!(yesno == 'Y' || yesno == 'N'));
    }while(yesno == 'Y');

    // Lägg till hela albumet i listan
    albvec.push_back(a);
}
//------------------------------------------------------------------------------
// findAlbumIdx
//------------------------------------------------------------------------------
// Uppgift: Söker igenom en vector efter en albumtitel som matchar bifogat
//          sökpredikat
// Indata : key (string), albumtitel att söka efter
// Utdata : idx (int), indexplatsen för eftersökt album eller last om ej träff
//------------------------------------------------------------------------------
int Jukebox::findAlbumIdx(string &key)
{
    // Hämta sökpredikatet som lambdafunktion
    auto it = find_if(albvec.begin(), albvec.end(), [&key](const Album &a)
    {
        return a.getAlbum() == key;
    });

    // Beräkna söksträngens index i vectorn
    int idx = distance(albvec.begin(), it);

    // Returnera index
    return idx;
}
//------------------------------------------------------------------------------
// delAlbum
//------------------------------------------------------------------------------
// Uppgift: Raderar ett album i spellistan
// Indata : -
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::delAlbum()
{
    // Läs bort huvudmenyns newline
    cin.get();
    // Sträng för att lagra sökpredikatet
    string key;

    // Fråga efter och mata in albumtitel att radera
    cout << "Input title of album to delete: ";
    getline(cin, key);

    // Hämta albumtitelns indexplats
    unsigned int idx = findAlbumIdx(key);

    // Om index är större än antal index i vectorn
    if(idx > albvec.size() - 1)
        // Skriv felmeddelande
        cout << "The album \"" << key << "\" was not found." << endl;
    // Om indexet finns inom vectorns ramar
    else
    {
        // Skriv information och radera givet album
        cout << "Erasing the album \"" << key << "\" from the database." << endl;
        albvec.erase(albvec.begin() + idx);
    }
}
//------------------------------------------------------------------------------
// printAlbumFormatted
//------------------------------------------------------------------------------
// Uppgift: Hjälpfunktion för att skriva ut ett album formatterat
// Indata : &idx (unsigned int)
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumFormatted(unsigned int &idx)
{
    // Skriv ut albumets titel
    cout << "Album title: " << albvec[idx].getAlbum() << endl;
    // Skriv ut antal låtar
    cout << "Nr of songs: " << albvec[idx].getNrSongs() << endl;
    // Skriv ut låtarna i format Artist - Titel - Speltid
    for(int i = 0; i < albvec[idx].getNrSongs(); i++)
    {
        cout << albvec[idx].getSongvec()[i].getArtist() << " - ";
        cout << albvec[idx].getSongvec()[i].getTitle() << " ";
        Time t = albvec[idx].getSongvec()[i].getDuration();
        printTime(t);
        cout << endl;
    }
    // Hämta albumets totala speltid
    Time runtime = albvec[idx].getAlbumDuration();
    // Skriv ut albumets totala speltid
    cout << "Total runtime: ";
    printTime(runtime);
    cout << endl;
}
//------------------------------------------------------------------------------
// printAlbumVector
//------------------------------------------------------------------------------
// Uppgift: Hjälpfunktion för att skriva ut albumvectorn formatterat
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumVector()
{
    for(auto idx: albvec)
    {
        // Skriv ut albumets titel
        cout << "Album title: " << idx.getAlbum() << endl;
        // Skriv ut antal låtar
        cout << "Nr of songs: " << idx.getNrSongs() << endl;
        // Skriv ut låtarna i format Artist - Titel - Speltid
        for(int i = 0; i < idx.getNrSongs(); i++)
        {
            cout << idx.getSongvec()[i].getArtist() << " - ";
            cout << idx.getSongvec()[i].getTitle() << " ";
            Time t = idx.getSongvec()[i].getDuration();
            printTime(t);
            cout << endl;
        }
        // Hämta albumets totala speltid
        Time runtime = idx.getAlbumDuration();
        // Skriv ut albumets totala speltid
        cout << "Total runtime: ";
        printTime(runtime);
        cout << endl << endl;
    }
}
//------------------------------------------------------------------------------
// printMenu
//------------------------------------------------------------------------------
// Uppgift: Undermenyn Print
// Indata : -
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printMenu()
{
    // Skapa objekt för huvudmenyn
    Menu printMenu;
    // Integer för antal val i menyn
    int menumax = 0;

    // Lägg till några menyalternativ och uppdatera
    // räknaren för antal menyalternativ
    printMenu.addItem("Print one album", true); // 1
    menumax++;
    printMenu.addItem("Print all albums by title", true); // 2
    menumax++;
    printMenu.addItem("Print all albums by duration", true); // 3
    menumax++;
    printMenu.addItem("Print album titles by title", true); // 4
    menumax++;
    printMenu.addItem("Print album titles by duration", true); // 5
    menumax++;
    printMenu.addItem("Back to main menu", true); // 6
    menumax++;

    // Kör menyn igen?
    bool again = true;

    // Loop för Printmenyn
    do
    {
        // Skriv ut menyalternativen
        printMenu.printMenuItems();

        // Hantera de olika valen
        switch(printMenu.getMenuChoice(menumax))
        {
            // Print one album
            case 1:
                // Om menyvalets enableflagga är true
                if(printMenu.getMenuvec()[0].getEnabled())
                    printAlbum();
                // Annars felmeddelande
                else
                    cout << "Print one album is disabled..." << endl;
                break;
            // Print all albums by title
            case 2:
                // Om menyvalets enableflagga är true
                if(printMenu.getMenuvec()[1].getEnabled())
                    printAlbumsByTitle();
                // Annars felmeddelande
                else
                    cout << "Print all albums by title is disabled..." << endl;
                break;
            // Print all albums by duration
            case 3:
                // Om menyvalets enableflagga är true
                if(printMenu.getMenuvec()[2].getEnabled())
                    printAlbumsByDuration();
                // Annars felmeddelande
                else
                    cout << "Print all albums by duration is disabled..." << endl;
                break;
            // Print album titles by title
            case 4:
                if(printMenu.getMenuvec()[3].getEnabled())
                    printAlbumTitles();
                else
                    cout << "Print album titles by title is disabled..." << endl;
                break;
            // Print album titles by duration
            case 5:
                if(printMenu.getMenuvec()[4].getEnabled())
                    printAlbumDurations();
                else
                    cout << "Print album titles by duration is disabled..." << endl;
                break;
            // Back to main menu
            case 6:
                // Om menyvalets enableflagga är true
                if(printMenu.getMenuvec()[5].getEnabled())
                {
                    // Avbryt loopen och återgå till huuvdmenyn
                    again = false;
                }
                // Annars felmeddelande
                else
                    cout << "Back to main menu is disabled..." << endl;
                break;
        }
    }while(again);
}
//------------------------------------------------------------------------------
// printAlbum
//------------------------------------------------------------------------------
// Uppgift: Skriv ut ett eftersökt album
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbum()
{
    // Läs bort huvudmenyns newline
    cin.get();
    // Sträng för sökpredikatet
    string key;
    Time t;

    cout << "Input album to search for: ";
    getline(cin, key);

    // Hämta albumtitelns indexplats
    unsigned int idx = findAlbumIdx(key);

    // Om index är större än antal index i vectorn
    if(idx > albvec.size() - 1)
        // Skriv felmeddelande
        cout << "The album \"" << key << "\" was not found." << endl;
    // Om indexet finns inom vectorns ramar
    else
    {
        // Skriv information om givet album
        cout << endl;
        printAlbumFormatted(idx);
        cout << endl;
    }
}
//------------------------------------------------------------------------------
// printAlbumsByTitle
//------------------------------------------------------------------------------
// Uppgift: Skriv ut info om alla album sorterade efter albumtitel
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumsByTitle()
{
    // Sortera albumen med hjälp av sökpredikat som lambdafunktion
    sort(albvec.begin(), albvec.end(), [](const Album &a, const Album &b)
    {
        return a.getAlbum() < b.getAlbum();
    });

    // Skriv ut albumvectorn
    printAlbumVector();
}
//------------------------------------------------------------------------------
// printAlbumsByDuration
//------------------------------------------------------------------------------
// Uppgift: Skriv ut info om alla album sorterade efter total speltid
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumsByDuration()
{
    // Sortera albumen med hjälp av sökpredikat som lambdafunktion
    sort(albvec.begin(), albvec.end(), [](const Album &a, const Album &b)
    {
        return a.getAlbumDuration() > b.getAlbumDuration();
    });

    // Skriv ut albumvectorn
    printAlbumVector();
}
//------------------------------------------------------------------------------
// printAlbumTitles
//------------------------------------------------------------------------------
// Uppgift: Skriv ut alla album sorterade efter albumtitel
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumTitles()
{
    // Sortera albumen med hjälp av sökpredikat som lambdafunktion
    sort(albvec.begin(), albvec.end(), [](const Album &a, const Album &b)
    {
        return a.getAlbum() < b.getAlbum();
    });

    // For each med lambdafunktion
    for_each(albvec.begin(), albvec.end(), [](const Album &a)
    {
        cout << a.getAlbum() << endl;
    });

    cout << endl;
}
//------------------------------------------------------------------------------
// printAlbumsByTitle
//------------------------------------------------------------------------------
// Uppgift: Skriv ut alla albumtitlar och totala speltider sorterade efter
//          speltid
// Indata :
// Utdata :
//------------------------------------------------------------------------------
void Jukebox::printAlbumDurations()
{
    // Sortera albumen med hjälp av sökpredikat som lambdafunktion
    sort(albvec.begin(), albvec.end(), [](const Album &a, const Album &b)
    {
        return a.getAlbumDuration() > b.getAlbumDuration();
    });

    // For each med lambdafunktion
    for_each(albvec.begin(), albvec.end(), [](const Album &a)
    {
        cout << left << setw(40);
        cout << a.getAlbum();
        Time runtime = a.getAlbumDuration();
        printTime(runtime);
        cout << endl;
    });

    cout << endl;
}
//------------------------------------------------------------------------------
// playMenu
//------------------------------------------------------------------------------
// Uppgift: Undermenyn Play (inte implementerad pga tidsbrist)
// Indata : -
// Utdata :
//------------------------------------------------------------------------------
//void Jukebox::playMenu()
//{

//}

// Konstruktor
Jukebox::Jukebox()
{
}

//------------------------------------------------------------------------------
// run
//------------------------------------------------------------------------------
// Uppgift: Huvudmeny som kör programmet
// Indata : -
// Utdata : Returnerar 0 vid lyckad körning och 1 vid fel
//------------------------------------------------------------------------------
int Jukebox::run()
{
    // Skapa objekt för huvudmenyn
    Menu menu;
    // Integer för antal val i menyn
    int menumax = 0;

    // Lägg till några menyalternativ och uppdatera
    // räknaren för antal menyalternativ
    menu.addItem("File...", true); // 1
    menumax++;
    menu.addItem("Add an album...", false); // 2
    menumax++;
    menu.addItem("Delete an album...", false); // 3
    menumax++;
    menu.addItem("Print...", false); // 4
    menumax++;
    menu.addItem("Play...", false); // 5
    menumax++;
    menu.addItem("Exit...", true); // 6
    menumax++;

    // Kör menyn igen?
    bool again = true;

    // Loop för huvudmenyn
    do
    {
        // Skriv ut menyalternativen
        menu.printMenuItems();

        // Hantera de olika valen
        switch(menu.getMenuChoice(menumax))
        {
            case 1:
                // Om menyvalets enableflagga är true
                if(menu.getMenuvec()[0].getEnabled())
                    fileMenu(menu);
                // Annars felmeddelande
                else
                    cout << "File is disabled..." << endl;
                break;
            case 2:
                // Om menyvalets enableflagga är true
                if(menu.getMenuvec()[1].getEnabled())
                    addAlbum();
                // Annars felmeddelande
                else
                    cout << "Add an album is disabled..." << endl;
                break;
            case 3:
                // Om menyvalets enableflagga är true
                if(menu.getMenuvec()[2].getEnabled())
                    delAlbum();
                // Annars felmeddelande
                else
                    cout << "Delete an album is disabled..." << endl;
                break;
            case 4:
                // Om menyvalets enableflagga är true
                if(menu.getMenuvec()[3].getEnabled())
                    printMenu();
                // Annars felmeddelande
                else
                    cout << "Print is disabled..." << endl;
                break;
            case 5:
                // Om menyvalets enableflagga är true
                if(menu.getMenuvec()[4].getEnabled())
                    cout << "Play menu not implemented yet..." << endl;
                // Annars felmeddelande
                else
                    cout << "Play is disabled..." << endl;
                break;
            case 6:
                cout << "Exiting program..." << endl;
                again = false;
        }
    }while(again);

    return 0;
}
