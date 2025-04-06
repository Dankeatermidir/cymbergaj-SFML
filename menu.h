#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include "gameloop.h"

//! klasa menu
class Menu
{
    sf::Font font;
    const static int n=3;
    std::array<sf::Text,n> option; //opcje
    std::array<std::string,n> texts = {"Restart","Resume","EXIT"}; //opcje nazwy
    int toogled=0; //które zaznaczone
    public:
    //! konstruktor - wczytywanie opcji w pętli
    Menu()
    {
        font.loadFromFile("Montserrat-Bold.ttf");
        for (int i=0;i<n;i++)
        {
            option[i].setFont(font);
            option[i].setFillColor(sf::Color::Red);
            option[i].setString(texts[i]);
            option[i].setCharacterSize(30);
            option[i].setPosition({820,180+(900/n)*i});
        };
        option[0].setFillColor(sf::Color::Blue);
    };
    ~Menu(){};
    //! rysowanie menu
    void show_menu(sf::RenderWindow & window)
    {
        window.clear(sf::Color::Black);
        for (int i=0;i<n;i++)
        {
            window.draw(option[i]);
        };
    };
    //! nawigowanie w górę
    void up()
    {
        option[toogled].setFillColor(sf::Color::Red);
        if (toogled==0)
            toogled=n-1;
        else
            toogled-=1;
        option[toogled].setFillColor(sf::Color::Blue);
    };
    //! nawigowanie w dół
    void down()
    {
        option[toogled].setFillColor(sf::Color::Red);
        if (toogled==n-1)
            toogled=0;
        else
            toogled+=1;
        option[toogled].setFillColor(sf::Color::Blue);
    };
    /*! wybór funkcji
    *0 - restart
    *1 - kontynuuj
    *2 - wyjście
    */
    void chose(Paddle & paddle1, Paddle & paddle2, Slot & slot1, Slot & slot2, Puck & puck, Banner & banner, sf::Clock & game_clock, sf::RenderWindow & window)
    {
        if (toogled==0)
            restart(paddle1,paddle2,slot1,slot2,puck,banner,game_clock,window);
        else if (toogled==1)
            up();
        else if (toogled==2)
            window.close();
    };
};
