#include "GlobalResources.h"

#include <iostream>
#include <sstream>

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

    /* Levels laden */
    for(int i=0; i<5; ++i)
    {
        std::ostringstream oss;
        oss << "./resources/level" << i << ".esl";
        std::string filename = oss.str();
        Level level;
        level.LoadFromFile(filename);
        levels.push_back(level);
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

int GlobalResources::GetNumberOfLevels() const
{
    return levels.size();
}

const Level& GlobalResources::GetLevel(int levelNumber) const
{
    if(levelNumber >= 0 && levelNumber < levels.size())
    {
        return levels[levelNumber];
    }
    else
    {
        return defaultLevel;
    }
}
