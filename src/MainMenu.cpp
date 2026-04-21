#include "MainMenu.h"

//pour le moment on gere que 2 boutons

MainMenu::MainMenu(){   
    cursor=0; 
}

MainMenu::~MainMenu(){


}


int MainMenu::getSelected(){
    return cursor;
}

void MainMenu::up(){
    if (cursor!=0)
    cursor--;
}

void MainMenu::down(){
    if(cursor<2 && cursor>=0)
    cursor++;
}


