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
    cursor=0;
}

void MainMenu::down(){
    cursor=1;
}