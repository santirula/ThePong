#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "PowerUp.hpp"

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    PowerUp powerUp;
    sf::Font font;
    sf::Text leftScoreText;
    sf::Text rightScoreText;
    sf::Text menuTitle;
    sf::Text menuInstruction;
    sf::Text menuControls;
    sf::Text menuPowerUps;
    sf::Text menuGoal;
    sf::Text pauseText;
    sf::Text gameOverText;
    sf::Text winnerText;
    int leftScore;
    int rightScore;
    GameState state;
    sf::Clock powerUpClock;
    float powerUpSpawnTime;
    
    void processEvents();
    void update(float dt);
    void render();
    void checkCollisions();
    void updateScore();
    void renderMenu();
    void renderPause();
    void renderGameOver();
    void resetGame();
    void checkPowerUpCollision();

public:
    Game();
    void run();
};

#endif