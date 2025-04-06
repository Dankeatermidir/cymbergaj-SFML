#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Slot.h"
#include "Paddle.h"
#include "soundboard.h"

//! klasa krążka
class Puck{
    public:
    const float waste=1; //współczynnik straty energii przy uderzeniu
    const float maks=5; //maksymalna prędkość
    const float resists=0.0001; //współczynnik oporów
    const float bindx=1860; //ograniczenia pozycji
    const float bindy=1020; //rozmiar okna - promień
    sf::Vector2f position={0.0,0.0}; //rzeczywista pozycja środka koła
    sf::Vector2f velocity={0.0,0.0};
    const int radius =60;
    const int outline =5;
    sf::CircleShape shape;
    //! konstruktor
    //! xy - wektor pozycji
    Puck(sf::Vector2f xy)
    {
        position.x = xy.x+radius;
        position.y = xy.y+radius;
        shape.setPosition(xy);
        shape.setFillColor(sf::Color::White);
        shape.setRadius(radius);
        shape.setOutlineThickness(outline);
        shape.setOutlineColor(sf::Color::Black);
    };
    ~Puck(){};
    //! funcja zderzenia krążka
    void bounce(Paddle & paddle, Soundboard & soundboard)
    {
        float vel;
        float cosinus;
        cosinus = (std::abs(position.y-paddle.position.y)/sqrt(std::pow((position.x-paddle.position.x),2.0)+std::pow((position.y-paddle.position.y),2.0)));
        vel=std::sqrt(std::pow(velocity.x-paddle.velocity.x,2.0)+std::pow(velocity.y-paddle.velocity.y,2.0));
        velocity.x=std::copysign(1,position.x-paddle.position.x)*vel*(1-cosinus*cosinus)*waste;
        velocity.y=std::copysign(1,position.y-paddle.position.y)*vel*cosinus*waste;
        if (std::abs(velocity.x)>maks)
            velocity.x=std::copysign(maks,velocity.x);
        if (std::abs(velocity.y)>maks)
            velocity.y=std::copysign(maks,velocity.y);
        paddle.velocity={0.0,0.0};
        soundboard.play_sound(0);
    };
    //! odbicie od ściany pionowej
    void bouncey(Soundboard & soundboard)
    {
        velocity.y=-velocity.y*waste;
        soundboard.play_sound(0);
    };
    //! odbicie od ściany poziomej
    void bouncex(Soundboard & soundboard)
    {
        velocity.x=-velocity.x*waste;
        soundboard.play_sound(0);
    };
    //! funkcja ruchu dla krążka
    void slide(Paddle & paddle1, Paddle & paddle2,Soundboard & soundboard)
    {
        if (std::abs(velocity.x)>0.2)
            velocity.x=velocity.x*(1-resists*std::abs(velocity.x));
        if (std::abs(velocity.y)>0.2)
            velocity.y=velocity.y*(1-resists*std::abs(velocity.y));
        if (position.x >=bindx || position.x <= radius)
            bouncex(soundboard);
        if (position.y >= bindy || position.y <= radius)
            bouncey(soundboard);
        if (std::sqrt(std::pow(position.x-paddle2.position.x-paddle2.velocity.x,2.0)+std::pow(position.y-paddle2.position.y-paddle2.velocity.y,2.0))<=2.0*radius)
            bounce(paddle2,soundboard);
        if (std::sqrt(std::pow(position.x-paddle1.position.x-paddle1.velocity.x,2.0)+std::pow(position.y-paddle1.position.y-paddle1.velocity.y,2.0))<=2.0*radius)
            bounce(paddle1,soundboard);
        shape.move(velocity);
        position={shape.getPosition().x+radius,shape.getPosition().y+radius};
    };
};
