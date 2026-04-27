#ifndef _MAINMENU_H
#define _MAINMENU_H


//nos include


/**
 * @class MainMenu
 *
 * @brief permet de gerere le menu d acceuil du jeu 
 *
 */

class MainMenu{
private:
    int cursor;


public:
/** 
 * @brief Constructeur par defaut de MainMenu
 *
 */
    MainMenu();
    /** 
    * @brief Destructeur par defaut de MainMenu
    *
    */
    ~MainMenu();
    /** 
    * @brief renvoie l option actuelement selectioner (pas cliquer mais selectionee)
    *
    * @return l id du "boutton" sur lequelle on hover
    */
    int getSelected();
    /** 
    * @brief bouge le curseur vers le haut
    *
    */
    void up();
    /** 
    * @brief bouge le curseur vers le bas
    *
    */
    void down();

};

#endif