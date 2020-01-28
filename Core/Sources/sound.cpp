#include <../Headers/sound.hpp>

void Sound::playMusic(){
    music.play();
    std::cout << music.getPitch() << std::endl;
}

void Sound::setTense(){
    music.setVolume( 100 );
    music.setPitch( 0.9 );
}

void Sound::setNormal(){
    music.setVolume( 25 );
    music.setPitch( 1 );
}