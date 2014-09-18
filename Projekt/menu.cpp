#include <iostream>
#include <limits>
#include "menu.h"
#include "jukefunc.h"
using namespace std;

// Konstruktorer
Menu::Menu()
{
    heading = "";
}

Menu::Menu(std::string pHeading)
{
    heading = pHeading;
}

// Setters
void Menu::setHeading(string pHeading)
{
    heading = pHeading;
}
//------------------------------------------------------------------------------
// addItem
//------------------------------------------------------------------------------
// Uppgift: Lägger till ett menyalternativ i menyn
// Indata : pMenuText (string), pEnabled (bool)
// Utdata :
//------------------------------------------------------------------------------
void Menu::addItem(string pMenuText, bool pEnabled)
{
    MenuItem menuitem;

    menuitem.setMenuText(pMenuText);
    menuitem.setEnabled(pEnabled);

    menuvec.push_back(menuitem);
}
//------------------------------------------------------------------------------
// printMenuItems
//------------------------------------------------------------------------------
// Uppgift: Skriver ut aktuell menys alternativ
// Indata : -
// Utdata :
//------------------------------------------------------------------------------
void Menu::printMenuItems()
{
    int numMenu = 1;

    // Stega igenom vectorn med menyvalen
    for(auto i: menuvec)
    {
        // Om valet är enabled
        if(i.getEnabled())
        {
            // Skriv ut valet samt numreringen
            cout << numMenu << ". " << i.getMenuText() << endl;
            numMenu++;
        }
        else
        {
            // Annars skriv ut valet med * som indikator för disabled
            cout << numMenu << ". " << i.getMenuText() << " (*)" << endl;
            numMenu++;
        }
    }
    cout << "(*) = disabled" << endl << endl;
}
//------------------------------------------------------------------------------
// getMenuChoice
//------------------------------------------------------------------------------
// Uppgift: Hämtar användarens val i menyer
// Indata : max (int), max antal val i menyn
// Utdata : Menyvalet som en int
//------------------------------------------------------------------------------
int Menu::getMenuChoice(int max)
{
    // Lagra menyvalet
    int menuChoice;

    // Fråga efter och läs in menyvalet med teckenverifiering
    while((cout << "Menyval: ")
           && (!(cin >> menuChoice)
               || menuChoice < 1
               || menuChoice > max))
    {
        invalidChoice(max);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Returnera menyvalet som en integer
    return menuChoice;
}
