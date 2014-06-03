#ifndef MENU_H
#define MENU_H
#include <vector>
#include "menuitem.h"

class Menu
{
    private:
        std::vector<MenuItem> menuvec;
        std::string heading;
    public:
        // Konstruktorer
        Menu();
        Menu(std::string pHeading);

        // Setters
        void setHeading(std::string pHeading);

        // Getters
        std::string getHeading() const {return heading;}
        std::vector<MenuItem> &getMenuvec() {return menuvec;}

        // Medlemsfunktioner
        void addItem(std::string pMenuText, bool pEnabled);
        void printMenuItems();
        int getMenuChoice(int max);

};

#endif // MENU_H
