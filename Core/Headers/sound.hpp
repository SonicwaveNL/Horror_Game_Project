#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

///@file
///\brief
///Sound class
///\details
/*class that produces the background music*/
class Sound {
  private:
    sf::Music music;
  public:
    Sound() {
        music.openFromFile("Resources/Sounds/ambient.ogg");
        music.setLoop(true);
    }

    
    ///\brief
    ///playMusic function
    ///\details
    /*plays the background music*/
    void playMusic();

    
    ///\brief
    ///setTense function
    ///\details
    /*setTense function that sets the music to tense mode*/
    void setTense();

    
    ///\brief
    ///setNormal
    ///\details
    /*setNormal function that sets the msuic to normal mode*/
    void setNormal();
};

#endif // SOUND_HPP