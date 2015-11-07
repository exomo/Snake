#ifndef GAMEOVER_H
#define GAMEOVER_H

namespace ExomoSnake
{

    class GameOver : public GameState
    {
    public:
        /** Default constructor */
        GameOver(int score);
        /** Default destructor */
        virtual ~GameOver();

        void handleEvent(const sf::Event& event) override;
        GameStatePtr updateGame(sf::Time elapsed, const std::shared_ptr<GameState>& currentState) override;
        void render(sf::RenderWindow& window) override;
    protected:
    private:
        /* Resourcen für Grafik und Text */
        sf::Font textFont;

        int score;
        bool exitRequested = false;
        bool startRequested = false;
    };

}
#endif // GAMEOVER_H
