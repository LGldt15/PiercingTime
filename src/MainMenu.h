#ifndef _MAINMENU_H
#define _MAINMENU_H


//nos include

#include "Player.h"

class MainMenu{
private:
    int spriteNotSelected[3];
    int spriteSelected[3];
    int idSelected;
    bool isSelectedLocal;//id=1
    bool isSelectedOnline;//id=2
    bool isSelectedSettings;//id=3
public:
    MainMenu();
    MainMenu(int sNS[3],int sS[3]);
    int getSelected();
    void modifSelected(Controls c);
};

#endif