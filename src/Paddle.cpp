#include "Paddle.hpp"

Paddle::Paddle(float width, float height, float posX, float posY, float paddleSpeed)
    : speed(paddleSpeed), baseHeight(height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(posX, posY);
}

void Paddle::moveUp(float dt, float windowTop) {
    if (shape.getPosition().y > windowTop) {
        shape.move(0.f, -speed * dt);
    }
}

void Paddle::moveDown(float dt, float windowBottom) {
    if (shape.getPosition().y + shape.getSize().y < windowBottom) {
        shape.move(0.f, speed * dt);
    }
}

void Paddle::growHeight(float amount) {
    sf::Vector2f currentSize = shape.getSize();
    float newHeight = currentSize.y + amount;
    if (newHeight > 300.f) newHeight = 300.f;
    shape.setSize(sf::Vector2f(currentSize.x, newHeight));
}

void Paddle::resetHeight() {
    sf::Vector2f currentSize = shape.getSize();
    shape.setSize(sf::Vector2f(currentSize.x, baseHeight));
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Paddle::getTop() const {
    return shape.getPosition().y;
}

float Paddle::getBottom() const {
    return shape.getPosition().y + shape.getSize().y;
}

float Paddle::getHeight() const {
    return shape.getSize().y;
}