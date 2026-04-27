
#pragma once
/**
 * @struct  Position
 *
 * @brief Structure exprimant une position, comme un vecteur 2D 
 *
 * 
 */

struct Position{
    float posX,posY;

    /**
    * @brief Calcule et renvoie la longeur du vecteur position 
    * 
    * @return longueur du vecteur
    */
    float length();
    /**
    * @brief Calcule et renvoie l angle du vecteur position 
    * 
    * @return angle du vecteur position en radiant
    */
    float angle(Position &p2);
    /**
    * @brief Calcule et renvoie le vecteur rotationé 
    * 
    * @param phi de rotation en radiant
    * 
    * @return vecteur position rotationé
    */
    Position rotate(const float &phi);
    /**
    * @brief Calcule et renvoie le vecteur rotationé 
    * 
    * @param c cosinus de l'angle de rotation
    * @param S sinus de l'angle de rotation
    * 
    * @return vecteur position rotationé
    */
    Position rotate(const float &c,const float &s);
    /**
    * @brief operateur d addition de deux position 
    * 
    * @param p2 deuxieme vecteur position a ajouter
    * 
    * @return vecteur position sommé
    */
    Position operator +(const Position &p2)const;
    /**
    * @brief operateur de soustraction de deux position 
    * 
    * @param p2 deuxieme vecteur position a soustraire
    * 
    * @return vecteur position résultat
    */
    Position operator -(const Position &p2)const;
    /**
    * @brief operateur d inversion de signe d une position 
    * 
    * @return vecteur position résultat
    */
    Position operator -() const;     
    /**
    * @brief operateur de produit scalaire de deux position 
    * 
    * @param p2 deuxieme vecteur position du profuit scalaire
    * 
    * @return vecteur position résultat
    */
    float operator *(const Position &p2)const;// dot product
    /**
    * @brief operateur de produit vectoriel de deux position 
    * 
    * @param p2 deuxieme vecteur position du profuit vectoriel
    * 
    * @return vecteur position résultat
    */
    float operator ^(const Position &p2)const;// cross product
    /**
    * @brief operateur de multiplication du vecteur position par un scalaire
    * 
    * @param q scalaire reel qui multiplie le vecteur position
    * 
    * @return vecteur position résultat
    */
    Position operator *(const float &q)const;
    /**
    * @brief operateur de division du vecteur position par un scalaire
    * 
    * @param q scalaire reel qui divise le vecteur position
    * 
    * @return vecteur position résultat
    */
    Position operator /(const float &q)const;
    /**
    * @brief Calcule et retourne la position d une intersection entre un rayon (vecteur position fixé) et un carré
    * 
    * @param origin point de départ du rayon
    * @param minX coordonée X du coin en haut à droite du carré
    * @param minY coordonée Y du coin en haut à droite du carré 
    * @param maxX coordonée X du coin en bas à gauche du carré
    * @param maxY coordonée Y du coin en bas à gauche du carré
    * 
    * @return position du point d intersection
    */
    Position squareIntersection(const Position &origin, unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY);//ray tracing en gros
};
