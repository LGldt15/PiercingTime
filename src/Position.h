struct Position{
    float posX,posY;

    float length();
    float angle(Position &p2);
    Position rotate(const float &phi);
    Position rotate(const float &c,const float &s);

    Position operator +(const Position &p2)const;
    Position operator -(const Position &p2)const;
    Position operator -() const;     

    float operator *(const Position &p2)const;// dot product
    float operator ^(const Position &p2)const;// cross product

    Position operator *(const float &q)const;
    Position operator /(const float &q)const;

    Position squareIntersection(const Position &origin, unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY);//ray tracing en gros
};
