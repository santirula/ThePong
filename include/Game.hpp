#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"

class Game {
private:
    sf::RenderWindow window;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    sf::Font font;
    sf::Text leftScoreText;
    sf::Text rightScoreText;
    int leftScore;
    int rightScore;
    
    void processEvents();
    void update(float dt);
    void render();
    void checkCollisions();
    void updateScore();

public:
    Game();
    void run();
};

#endif