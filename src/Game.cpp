#include "Game.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 600), "Pong Game"),
      leftPaddle(15.f, 100.f, 30.f, 250.f, 400.f),
      rightPaddle(15.f, 100.f, 755.f, 250.f, 400.f),
      ball(10.f, 300.f),
      leftScore(0),
      rightScore(0) {
    
    window.setFramerateLimit(60);
    
    // Si no tienes una fuente, usa la fuente por defecto del sistema
    // o descarga una fuente .ttf y ponla en tu proyecto
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente. Usando texto sin fuente." << std::endl;
    }
    
    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(50);
    leftScoreText.setFillColor(sf::Color::White);
    leftScoreText.setPosition(300.f, 20.f);
    leftScoreText.setString("0");
    
    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(50);
    rightScoreText.setFillColor(sf::Color::White);
    rightScoreText.setPosition(480.f, 20.f);
    rightScoreText.setString("0");
    
    ball.reset(800.f, 600.f);
}

void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}

void Game::update(float dt) {
    // Control del paddle izquierdo (W/S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        leftPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        leftPaddle.moveDown(dt, 600.f);
    }
    
    // Control del paddle derecho (Flechas Arriba/Abajo)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rightPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rightPaddle.moveDown(dt, 600.f);
    }
    
    // Actualizar la pelota
    ball.update(dt);
    
    // Colisiones
    checkCollisions();
    
    // Actualizar puntuación
    updateScore();
}

void Game::checkCollisions() {
    sf::Vector2f ballPos = ball.getPosition();
    
    // Colisión con bordes superior e inferior
    if (ballPos.y <= 0 || ballPos.y >= 600.f) {
        ball.reverseY();
    }
    
    // Colisión con paddles
    if (ball.getBounds().intersects(leftPaddle.getBounds())) {
        ball.reverseX();
        ball.setPosition(leftPaddle.getBounds().left + leftPaddle.getBounds().width + 10.f, ballPos.y);
    }
    
    if (ball.getBounds().intersects(rightPaddle.getBounds())) {
        ball.reverseX();
        ball.setPosition(rightPaddle.getBounds().left - 10.f, ballPos.y);
    }
}

void Game::updateScore() {
    sf::Vector2f ballPos = ball.getPosition();
    
    // Punto para el jugador derecho
    if (ballPos.x < 0) {
        rightScore++;
        rightScoreText.setString(std::to_string(rightScore));
        ball.reset(800.f, 600.f);
    }
    
    // Punto para el jugador izquierdo
    if (ballPos.x > 800.f) {
        leftScore++;
        leftScoreText.setString(std::to_string(leftScore));
        ball.reset(800.f, 600.f);
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    // Dibujar línea central
    sf::RectangleShape centerLine(sf::Vector2f(5.f, 600.f));
    centerLine.setPosition(397.5f, 0.f);
    centerLine.setFillColor(sf::Color(100, 100, 100));
    window.draw(centerLine);
    
    leftPaddle.draw(window);
    rightPaddle.draw(window);
    ball.draw(window);
    window.draw(leftScoreText);
    window.draw(rightScoreText);
    
    window.display();
}