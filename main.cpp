#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Slot.h"
#include "Paddle.h"
#include "Puck.h"
#include "Banner.h"
#include "gameloop.h"
#include "menu.h"
#include "soundboard.h"

sf::Texture tex; //ładowanie grafiki tła
sf::Sprite background;
int main()
{
    create_background(background,tex); //ładowanie tła
    Soundboard soundboard; //ładowanie dźwięków
    sf::RenderWindow window(sf::VideoMode(1920, 1080,32),"airhockey", sf::Style::Fullscreen);
    Paddle paddle1(sf::Color::Red,{150,480},60,60,1); //tworzenie graczy
    Paddle paddle2(sf::Color::Blue,{1640,480},1260,60,1);
    Slot slot1(sf::Color::Red,{0,340},1); //tworzenie bramek
    Slot slot2(sf::Color::Blue,{1910,340},2);
    Puck puck({500,480}); //tworzenie krążka
    sf::Clock game_clock; //tworzenie zegara
    Banner banner;
    bool paused = false;
    Menu m;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //! zamykanie gry
            if (event.type == sf::Event::Closed)
                window.close();
            //! pauzowanie gry i operacje w menu
            if (event.type == (sf::Event::KeyPressed))
            {
                //! pauza
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (!paused)
                        banner.save_state(game_clock);
                    paused=!paused;
                    game_clock.restart();
                };
                //! operacje w menu
                if (paused)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        m.up();
                    if (event.key.code == sf::Keyboard::Down)
                        m.down();
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        m.chose(paddle1,paddle2,slot1,slot2,puck,banner,game_clock,window);
                        paused=!paused;
                    };
                    game_clock.restart();
                };
            };
        };
        if (paused)
            m.show_menu(window);
        if (!paused)
        {
            gameloop(paddle1,paddle2,slot1,slot2,puck,banner,game_clock,soundboard,window,background);
        };
        window.display();
    };
    return 0;
};
