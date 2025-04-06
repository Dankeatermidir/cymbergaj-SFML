#pragma once
#include <array>
#include <SFML/Audio.hpp>
#include <string>
//! zbiór dźwięków gry
class Soundboard
{
    static const int n=3; //ilość dźwięków
    std::array<sf::SoundBuffer,n> buffers;
    std::array<std::string,n> names= {"bounce","goal","won"}; // nazwy plików .wav
    std::array<sf::Sound,n> sounds; // zbiór dźwięków
    public:
    //! konstruktor - wczytywanie plików w pętli
    Soundboard()
    {
        for (int i=0;i<n;i++)
        {
            buffers[i].loadFromFile("sounds/"+names[i]+".wav");
            sounds[i].setBuffer(buffers[i]);
        };
    };
    ~Soundboard(){};
    /*! Odtwarzanie dźwięku
    *0 - zderzenie
    *1 - gol
    *2 - wygrana/początek gry
    */
    //! odtwarzanie dźwięków
    void play_sound(int i)
    {
        sounds[i].play();
    };
};
