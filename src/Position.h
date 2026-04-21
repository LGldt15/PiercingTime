struct Position{
    float posX,posY;
    float length();
    Position operator +(const Position &p2)const;
    Position operator -(const Position &p2)const;
    Position operator *(const float &q)const;
    Position operator /(const float &q)const;

};
