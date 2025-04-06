#pragma once
#include <SFML/Graphics.hpp>

//! klasa bramki
class Slot{
    public:
    int player;
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Color color;
    sf::Vector2f Size={10,400};
    /*! konstruktor
    *c - kolor
    *xy - wektor pozycji
    *p - numer gracza
    */
    Slot(sf::Color c, sf::Vector2f xy,int p)
    {
        player=p;
        shape.setPosition(xy);
        shape.setFillColor(c);
        shape.setSize(Size);
        shape.setOutlineColor(c);
        position= {xy.x,xy.y+(Size.y/2)};
    };
    ~Slot(){};
};
