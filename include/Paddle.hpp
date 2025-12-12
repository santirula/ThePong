#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle(float width, float height, float posX, float posY, float paddleSpeed);
    void moveUp(float dt, float windowTop);
    void moveDown(float dt, float windowBottom);
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
    float getTop() const;
    float getBottom() const;
};

#endif