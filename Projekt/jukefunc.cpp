#include <iostream>
#include "jukefunc.h"
using namespace std;

//------------------------------------------------------------------------------
// invalidChoice
//------------------------------------------------------------------------------
// Uppgift: Skriver ut felmeddelande vid ogiltig inmatning
// Indata : max (int), max antal val i menyn
// Utdata : -
//------------------------------------------------------------------------------
void invalidChoice(int max)
{
    cout << "Please enter a valid choice between 1 and " << max << "." << endl;
}
//------------------------------------------------------------------------------
// yesNoMenu
//------------------------------------------------------------------------------
// Uppgift: Hanterar valet för att lägga till ytterligare en låt
// Indata : -
// Utdata : -
//------------------------------------------------------------------------------
char yesNoMenu()
{
    // char för att lagra menyvalet
    char choice;

    // Läs bort retur
    cin.get();
    cout << endl << "Add another song (y/n)? ";
    // Läs ett tecken (y eller n)
    cin.get(choice);
    // Konvertera valet till versal
    choice = toupper(choice);

    // Returnera valet
    return choice;
}
