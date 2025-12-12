#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
    float baseSpeed;
    int lastPaddleHit;

public:
    Ball(float radius, float initialSpeed);
    void update(float dt);
    void reset(float windowWidth, float windowHeight);
    void reverseX();
    void reverseY();
    void increaseSpeed(float amount);
    void setLastPaddleHit(int paddle);
    int getLastPaddleHit() const;
    void setAngleFromPaddle(float hitPosition);
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
};

#endif