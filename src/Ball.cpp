#include "Ball.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

Ball::Ball(float radius, float initialSpeed) : speed(initialSpeed), baseSpeed(initialSpeed), lastPaddleHit(0) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(radius, radius);
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    float angle = (std::rand() % 60 - 30) * 3.14159f / 180.f;
    velocity.x = std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
    
    if (std::rand() % 2 == 0)
        velocity.x = -velocity.x;
}

void Ball::update(float dt) {
    shape.move(velocity * dt);
}

void Ball::reset(float windowWidth, float windowHeight) {
    shape.setPosition(windowWidth / 2.f, windowHeight / 2.f);
    speed = baseSpeed;
    lastPaddleHit = 0;
    
    float angle = (std::rand() % 60 - 30) * 3.14159f / 180.f;
    velocity.x = std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
    
    if (std::rand() % 2 == 0)
        velocity.x = -velocity.x;
}

void Ball::reverseX() {
    velocity.x = -velocity.x;
}

void Ball::reverseY() {
    velocity.y = -velocity.y;
}

void Ball::increaseSpeed(float amount) {
    speed += amount;
    float currentAngle = std::atan2(velocity.y, velocity.x);
    velocity.x = std::cos(currentAngle) * speed;
    velocity.y = std::sin(currentAngle) * speed;
}

void Ball::setLastPaddleHit(int paddle) {
    lastPaddleHit = paddle;
}

int Ball::getLastPaddleHit() const {
    return lastPaddleHit;
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}