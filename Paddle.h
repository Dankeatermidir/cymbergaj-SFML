#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

//! klasa gracza
class Paddle{
    public:
    float bindx; //ograniczenia pozycji
    float bindy;
    int player;
    sf::Vector2f position={0.0,0.0}; //rzeczywista pozycja środka
    sf::Vector2f velocity;
    const int radius = 60;
    sf::Color color;
    sf::CircleShape shape;
    /*! konstruktor
    *C - kolor
    *xy - wektor pozycji
    *x - ograniczenie w poziomie
    *y - ograniczenie w pionie
    *g - numer gracza
    */
    Paddle(sf::Color C, sf::Vector2f xy, float x, float y, int g)
    {
        player=g;
        bindx=x;
        bindy=y;
        position.x = xy.x+radius;
        position.y = xy.y+radius;
        color=C;
        shape.setPosition(position);
        shape.setFillColor(color);
        shape.setRadius(radius);
        shape.setOutlineThickness(5);
        shape.setOutlineColor(sf::Color::Black);
    };
    //! ustawianie wektorów prędkosci
    void setvel(float x,float y)
    {
        velocity.x+=x;
        velocity.y+=y;
    }
    ~Paddle(){};
    //! funkcja ruchu dla ręki z wyrównywaniem prędkości
    void movef()
    {
            if (position.x+velocity.x<=bindx||position.x+velocity.x>=(600+bindx))
            {
                velocity.x=0.0;
            };
            if (position.y+velocity.y<=bindy||position.y+velocity.y>=(bindy+960))
            {
                velocity.y=0.0;
            };
            if (velocity.x!=0&&velocity.y!=0)
            {
                velocity.x*=0.71;
                velocity.y*=0.71;
            };
            shape.move(velocity);
            position={shape.getPosition().x+radius,shape.getPosition().y+radius};
    };
};
