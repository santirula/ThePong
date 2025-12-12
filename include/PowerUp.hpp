#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

enum PowerUpType {
    GROW_PADDLE,
    SPEED_BALL
};

class PowerUp {
private:
    sf::RectangleShape shape;
    PowerUpType type;
    bool active;

public:
    PowerUp();
    void spawn(float windowWidth, float windowHeight);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    PowerUpType getType() const;
    bool isActive() const;
    void deactivate();
};

#endif