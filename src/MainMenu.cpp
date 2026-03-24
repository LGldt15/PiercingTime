#include "MainMenu.h"

MainMenu::MainMenu(){
        for (int i=0;i<3;i++){
        spriteNotSelected[i]=0;
        spriteSelected[i]=0;
    }
    idSelected=0;
}
MainMenu::MainMenu(int sNS[3],int sS[3]){
    for (int i=0;i<3;i++){
        spriteNotSelected[i]=sNS[i];
        spriteSelected[i]=sS[i];

    }
}

int MainMenu::getSelected(){
    return  0;
}

void MainMenu::modifSelected(Controls c){
    if (c.up)idSelected=((idSelected+1)%3)+1;
    if (c.down)idSelected=((idSelected-1)%3)+1;
}
