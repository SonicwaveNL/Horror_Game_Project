#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

///@file
///\brief
/// Sound class.
///\details
/*Class that produces the background music.*/
class Sound {
  private:
    sf::Music music;

  public:
    ///\brief
    ///Sound class constructor.
    Sound() {
        music.openFromFile("Resources/Sounds/ambient.ogg");
        music.setLoop(true);
    }

    ///\brief
    /// Plays the music.
    void playMusic();

    ///\brief
    ///Makes the music sound more tense.
    void setTense();

    ///\brief
    ///Makes the music normal (again).
    void setNormal();
};

#endif // SOUND_HPP