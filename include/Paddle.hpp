#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;
    float baseHeight;

public:
    Paddle(float width, float height, float posX, float posY, float paddleSpeed);
    void moveUp(float dt, float windowTop);
    void moveDown(float dt, float windowBottom);
    void growHeight(float amount);
    void resetHeight();
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    float getTop() const;
    float getBottom() const;
    float getHeight() const;
};

#endif