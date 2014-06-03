#include "menuitem.h"
using namespace std;

// Standardkonstruktor
MenuItem::MenuItem()
{
    menuText = "";
    enabled = false;
}

// Överlagrad konstruktor
MenuItem::MenuItem(string pMenuText, bool pEnabled)
{
    menuText = pMenuText;
    enabled = pEnabled;
}

// Setters
void MenuItem::setMenuText(string pMenuText)
{
    menuText = pMenuText;
}

void MenuItem::setEnabled(bool pEnabled)
{
    enabled = pEnabled;
}
