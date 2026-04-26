#include "IHM.h"
//#include <random>
#include <time.h>


int main(){
    srand(time(NULL));
    IHM game;
    game.init();
    game.app();


    return 0;
}