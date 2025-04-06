#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Slot.h"

//! klasa bannera
class Banner{
    public:
    int points1=0; //punkty graczy
    int points2=0;
    int state=0; //stan zegara
    sf::Font font;
    sf::RectangleShape shape;
    sf::Vector2f Size = {1920,40};
    sf::Text player1;
    sf::Text player2;
    sf::Text timer; //zegar
    sf::Text counter1; //liczniki punktów
    sf::Text counter2;
    //! konstruktor rysuje całość banera z wyzerowanymi wartościami
    Banner()
    {
        font.loadFromFile("Montserrat-Bold.ttf");
        shape.setPosition({0,0});
        shape.setFillColor(sf::Color{ 70, 70, 70, 200 });
        shape.setSize(Size);
        timer.setFont(font);
        timer.setString("00:00");
        timer.setFillColor(sf::Color::Green);
        timer.setCharacterSize(30);
        timer.setPosition({850,5});
        player1.setFont(font);
        player1.setString("PLAYER 1");
        player1.setFillColor(sf::Color::Red);
        player1.setCharacterSize(30);
        player1.setPosition({600,5});
        player2.setFont(font);
        player2.setString("PLAYER 2");
        player2.setFillColor(sf::Color::Blue);
        player2.setCharacterSize(30);
        player2.setPosition({1100,5});
        counter1.setFont(font);
        counter1.setString("0");
        counter1.setFillColor(sf::Color::Red);
        counter1.setCharacterSize(30);
        counter1.setPosition({500,5});
        counter2.setFont(font);
        counter2.setString("0");
        counter2.setFillColor(sf::Color::Blue);
        counter2.setCharacterSize(30);
        counter2.setPosition({1350,5});
    };
    //! zapisywanie stanu zegara gry (używane przy pauzie)
    void save_state(sf::Clock & game_clock)
    {
        state+=game_clock.getElapsedTime().asMilliseconds();
        game_clock.restart();
    };
    //! aktualizacja zegara wyświetlanego na bannerze
    void update_timer(sf::Clock & game_clock)
    {
        int seconds = (game_clock.getElapsedTime().asMilliseconds()+state)/1000;
        std::string s = std::to_string(seconds/60)+":"+std::to_string(seconds%60);
        timer.setString(s);
    };
    //! aktualizacja
    void update_points(const Slot & slot)
    {
        if (slot.player==2)
        {
            points1+=1;
            counter1.setString(std::to_string(points1));
        }
        else
        {
            points2+=1;
            counter2.setString(std::to_string(points2));
        };
    };
    //! zebrane wszystkie obiekty bannera do narysowania
    void show_banner(sf::RenderWindow & window)
    {
        window.draw(shape);
        window.draw(timer);
        window.draw(player1);
        window.draw(player2);
        window.draw(counter1);
        window.draw(counter2);
    };
    //! zerowanie wartości na bannerze
    void clean()
    {
        points1=0;
        points2=0;
        state=0;
        counter1.setString(std::to_string(points1));
        counter2.setString(std::to_string(points2));
        timer.setString("00:00");
    };
    ~Banner(){};
};
