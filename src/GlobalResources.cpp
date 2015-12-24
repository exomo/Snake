#include "GlobalResources.h"

#include <iostream>

using namespace ExomoSnake;

void GlobalResources::LoadResources()
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/Amaranth-Italic.otf"))
    {
        throw resource_exception("./resources/Amaranth-Italic.otf");
    }

    /* Musik laden, die im Spiel läuft. */
    if (!backgroundMusic.loadFromFile("./resources/bensound-clearday.ogg"))
    {
        throw resource_exception("./resources/bensound-clearday.ogg");
    }

    /* Soundeffekte laden */
    if (!appleSound.loadFromFile("./resources/biteapple.ogg"))
    {
        throw resource_exception("./resources/biteapple.ogg");
    }
}

const sf::Font& GlobalResources::GetFont() const
{
    return textFont;
}

const sf::SoundBuffer& GlobalResources::GetBackgroundMusic() const
{
    return backgroundMusic;
}

const sf::SoundBuffer& GlobalResources::GetAppleSound() const
{
    return appleSound;
}
