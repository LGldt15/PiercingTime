#include "Player.h"
void Player::move(const Controls &c){
    float dx=0.0f; // variation de position en largeur
    float dy=0.0f; // variation de position en hauteur
    if(c.up) dy-= speed;
    if(c.down) dy+= speed;
    if(c.right) dx+= speed;
    if(c.left) dx-= speed;
    if(dx*dy!=0){dx*=0.70710678118; dy*=0.70710678118;} //normalisation à speed (multiplication par sqrt(2)/2) si cas diagonal
    position.x+=dx; //ajout à la position courante
    position.y+=dy;
}
