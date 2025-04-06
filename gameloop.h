#pragma once
#include <SFML/Graphics.hpp>
#include "Puck.h"
#include "Slot.h"
#include "Paddle.h"
#include "Banner.h"
#include "soundboard.h"
#include <thread>

//! czyczczenie boiska
void reset_map (int  player, Puck & puck,Paddle & paddle1, Paddle & paddle2,sf::RenderWindow & window)
{
    window.clear();
    if (player==2)
        puck.shape.setPosition({1400,480});
    else
        puck.shape.setPosition({500,480});
    puck.velocity={0,0};
    puck.position=puck.shape.getPosition();
    paddle2.shape.setPosition({1640,480});
    paddle1.shape.setPosition({150,480});
};
//! funkcja po trafieniu do bramki
void goal (Slot & slot, Puck & puck,Banner & banner,Paddle & paddle1, Paddle & paddle2, sf::RenderWindow & window)
{
    reset_map(slot.player,puck,paddle1,paddle2,window);
    banner.update_points(slot);
};
//! restart gry
void restart(Paddle & paddle1, Paddle & paddle2, Slot & slot1, Slot & slot2, Puck & puck, Banner & banner, sf::Clock & game_clock, sf::RenderWindow & window)
{
    reset_map(1,puck,paddle1,paddle2,window);
    banner.clean();
    game_clock.restart();
};
//! tworzenie tła
void create_background(sf::Sprite & image,sf::Texture & tex)
{
    tex.loadFromFile("background.png");
    image.setTexture(tex);
    image.setOrigin(0,0);
};
//! pętla gry
void gameloop(Paddle & paddle1, Paddle & paddle2, Slot & slot1, Slot & slot2, Puck & puck, Banner & banner, sf::Clock & game_clock,Soundboard & soundboard, sf::RenderWindow & window,sf::Sprite & background)
{
        paddle1.velocity={0.0,0.0};
        paddle2.velocity={0.0,0.0};
        banner.update_timer(game_clock);
        //! sterowanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            paddle1.setvel(-1,0);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            paddle1.setvel(1,0);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            paddle1.setvel(0,-1);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            paddle1.setvel(0,1);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            paddle2.setvel(-1,0);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            paddle2.setvel(1,0);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            paddle2.setvel(0,-1);
        };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            paddle2.setvel(0,1);
        };
        //! ruchy krążka i graczy
        puck.slide(paddle1,paddle2,soundboard);
        paddle1.movef();
        paddle2.movef();
        if (std::abs(slot1.position.x-puck.position.x)<=puck.radius&&std::abs(slot1.position.y-puck.position.y)<=slot1.Size.y/2 - puck.radius*0.3)
        {
            goal(slot1,puck,banner,paddle1,paddle2,window);
            soundboard.play_sound(1);
        };
        if (std::abs(slot2.position.x-puck.position.x)<=puck.radius&&std::abs(slot2.position.y-puck.position.y)<=slot2.Size.y/2 - puck.radius*0.3)
        {
            goal(slot2,puck,banner,paddle1,paddle2,window);
            soundboard.play_sound(1);
        };
        window.draw(background); //rysowanie wszystkiego po kolei
        window.draw(paddle1.shape);
        window.draw(paddle2.shape);
        window.draw(slot1.shape);
        window.draw(slot2.shape);
        window.draw(puck.shape);
        banner.show_banner(window);
};

