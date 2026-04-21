#ifndef _MAINMENU_H
#define _MAINMENU_H


//nos include



class MainMenu{
private:
    int cursor;


public:
    MainMenu();
    ~MainMenu();
    int getSelected();
    void up();
    void down();

};

#endif