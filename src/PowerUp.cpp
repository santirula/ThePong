#include "PowerUp.hpp"
#include <cstdlib>
#include <ctime>

PowerUp::PowerUp() : active(false), type(GROW_PADDLE) {
    shape.setSize(sf::Vector2f(20.f, 20.f));
    shape.setOrigin(10.f, 10.f);
    shape.setFillColor(sf::Color::Green);
}

void PowerUp::spawn(float windowWidth, float windowHeight) {
    active = true;
    
    // Tipo aleatorio
    type = (std::rand() % 2 == 0) ? GROW_PADDLE : SPEED_BALL;
    
    // Posición aleatoria
    float x = 200.f + std::rand() % static_cast<int>(windowWidth - 400.f);
    float y = 100.f + std::rand() % static_cast<int>(windowHeight - 200.f);
    shape.setPosition(x, y);
    
    // Color según tipo
    if (type == GROW_PADDLE) {
        shape.setFillColor(sf::Color::Green);
    } else {
        shape.setFillColor(sf::Color::Red);
    }
}

void PowerUp::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(shape);
    }
}

sf::FloatRect PowerUp::getBounds() const {
    return shape.getGlobalBounds();
}

PowerUpType PowerUp::getType() const {
    return type;
}

bool PowerUp::isActive() const {
    return active;
}

void PowerUp::deactivate() {
    active = false;
}