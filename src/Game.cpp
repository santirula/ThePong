#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

Game::Game()
    : window(sf::VideoMode(800, 600), "Pong Game - Extended Edition"),
      leftPaddle(15.f, 100.f, 30.f, 250.f, 400.f),
      rightPaddle(15.f, 100.f, 755.f, 250.f, 400.f),
      ball(10.f, 300.f),
      leftScore(0),
      rightScore(0),
      state(MENU),
      powerUpSpawnTime(5.f) {
    
    window.setFramerateLimit(60);
    
    // Intentar cargar diferentes fuentes del sistema
    bool fontLoaded = false;
    
    std::vector<std::string> fontPaths = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "arial.ttf",
        "fonts/arial.ttf"
    };
    
    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            fontLoaded = true;
            std::cout << "Fuente cargada: " << path << std::endl;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cerr << "ADVERTENCIA: No se pudo cargar ninguna fuente del sistema." << std::endl;
        std::cerr << "El juego funcionara pero sin texto visible." << std::endl;
        std::cerr << "Solucion: Descarga una fuente .ttf y colocala en la carpeta del ejecutable." << std::endl;
    }
    
    // Textos de puntuación
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
    
    // Menú mejorado
    menuTitle.setFont(font);
    menuTitle.setCharacterSize(120);
    menuTitle.setFillColor(sf::Color::Cyan);
    menuTitle.setString("PONG");
    menuTitle.setStyle(sf::Text::Bold);
    sf::FloatRect titleBounds = menuTitle.getLocalBounds();
    menuTitle.setOrigin(titleBounds.left + titleBounds.width/2.0f, titleBounds.top + titleBounds.height/2.0f);
    menuTitle.setPosition(400.f, 120.f);
    
    menuInstruction.setFont(font);
    menuInstruction.setCharacterSize(24);
    menuInstruction.setFillColor(sf::Color(200, 200, 200));
    menuInstruction.setString("Presiona ESPACIO para comenzar");
    sf::FloatRect instrBounds = menuInstruction.getLocalBounds();
    menuInstruction.setOrigin(instrBounds.left + instrBounds.width/2.0f, instrBounds.top + instrBounds.height/2.0f);
    menuInstruction.setPosition(400.f, 500.f);
    
    // Controles
    menuControls.setFont(font);
    menuControls.setCharacterSize(20);
    menuControls.setFillColor(sf::Color::White);
    menuControls.setString("CONTROLES\n\nJugador 1: W / S\nJugador 2: Flechas");
    sf::FloatRect ctrlBounds = menuControls.getLocalBounds();
    menuControls.setOrigin(ctrlBounds.left + ctrlBounds.width/2.0f, ctrlBounds.top);
    menuControls.setPosition(250.f, 250.f);
    
    // Power-ups
    menuPowerUps.setFont(font);
    menuPowerUps.setCharacterSize(20);
    menuPowerUps.setFillColor(sf::Color::White);
    menuPowerUps.setString("POWER-UPS\n\nVerde: Crece tu paleta\nRojo: Acelera pelota");
    sf::FloatRect pwrBounds = menuPowerUps.getLocalBounds();
    menuPowerUps.setOrigin(pwrBounds.left + pwrBounds.width/2.0f, pwrBounds.top);
    menuPowerUps.setPosition(550.f, 250.f);
    
    // Objetivo
    menuGoal.setFont(font);
    menuGoal.setCharacterSize(22);
    menuGoal.setFillColor(sf::Color(255, 215, 0));
    menuGoal.setString("Primer jugador en llegar a 10 puntos GANA");
    sf::FloatRect goalBounds = menuGoal.getLocalBounds();
    menuGoal.setOrigin(goalBounds.left + goalBounds.width/2.0f, goalBounds.top);
    menuGoal.setPosition(400.f, 400.f);
    
    // Pausa
    pauseText.setFont(font);
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("PAUSA");
    pauseText.setPosition(280.f, 250.f);
    
    // Game Over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(180.f, 200.f);
    
    winnerText.setFont(font);
    winnerText.setCharacterSize(40);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(200.f, 300.f);
    
    ball.reset(800.f, 600.f);
}

void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        processEvents();
        
        if (state == PLAYING) {
            update(dt);
        }
        
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (state == PLAYING) {
                    state = PAUSED;
                } else if (state == PAUSED) {
                    state = PLAYING;
                } else {
                    window.close();
                }
            }
            
            if (event.key.code == sf::Keyboard::Space) {
                if (state == MENU) {
                    state = PLAYING;
                    powerUpClock.restart();
                } else if (state == PAUSED) {
                    state = PLAYING;
                } else if (state == GAME_OVER) {
                    resetGame();
                    state = MENU;
                }
            }
        }
    }
}

void Game::update(float dt) {
    // Control del paddle izquierdo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        leftPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        leftPaddle.moveDown(dt, 600.f);
    }
    
    // Control del paddle derecho
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        rightPaddle.moveUp(dt, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        rightPaddle.moveDown(dt, 600.f);
    }
    
    ball.update(dt);
    checkCollisions();
    updateScore();
    
    // Generar power-ups
    if (powerUpClock.getElapsedTime().asSeconds() > powerUpSpawnTime && !powerUp.isActive()) {
        powerUp.spawn(800.f, 600.f);
        powerUpClock.restart();
        powerUpSpawnTime = 5.f + (std::rand() % 10);
    }
    
    checkPowerUpCollision();
}

void Game::checkCollisions() {
    sf::Vector2f ballPos = ball.getPosition();
    
    if (ballPos.y <= 10.f || ballPos.y >= 590.f) {
        ball.reverseY();
    }
    
    if (ball.getBounds().intersects(leftPaddle.getBounds())) {
        ball.reverseX();
        ball.setPosition(leftPaddle.getBounds().left + leftPaddle.getBounds().width + 10.f, ballPos.y);
        ball.setLastPaddleHit(1);
    }
    
    if (ball.getBounds().intersects(rightPaddle.getBounds())) {
        ball.reverseX();
        ball.setPosition(rightPaddle.getBounds().left - 10.f, ballPos.y);
        ball.setLastPaddleHit(2);
    }
}

void Game::checkPowerUpCollision() {
    if (!powerUp.isActive()) return;
    
    if (ball.getBounds().intersects(powerUp.getBounds())) {
        PowerUpType type = powerUp.getType();
        int lastHit = ball.getLastPaddleHit();
        
        if (type == GROW_PADDLE) {
            if (lastHit == 1) {
                leftPaddle.growHeight(40.f);
            } else if (lastHit == 2) {
                rightPaddle.growHeight(40.f);
            }
        } else if (type == SPEED_BALL) {
            ball.increaseSpeed(50.f);
        }
        
        powerUp.deactivate();
    }
}

void Game::updateScore() {
    sf::Vector2f ballPos = ball.getPosition();
    
    if (ballPos.x < 0) {
        rightScore++;
        rightScoreText.setString(std::to_string(rightScore));
        ball.reset(800.f, 600.f);
        leftPaddle.resetHeight();
        rightPaddle.resetHeight();
        
        if (rightScore >= 10) {
            state = GAME_OVER;
            winnerText.setString("Jugador 2 Gana!\n\nPresiona ESPACIO");
        }
    }
    
    if (ballPos.x > 800.f) {
        leftScore++;
        leftScoreText.setString(std::to_string(leftScore));
        ball.reset(800.f, 600.f);
        leftPaddle.resetHeight();
        rightPaddle.resetHeight();
        
        if (leftScore >= 10) {
            state = GAME_OVER;
            winnerText.setString("Jugador 1 Gana!\n\nPresiona ESPACIO");
        }
    }
}

void Game::resetGame() {
    leftScore = 0;
    rightScore = 0;
    leftScoreText.setString("0");
    rightScoreText.setString("0");
    ball.reset(800.f, 600.f);
    leftPaddle.resetHeight();
    rightPaddle.resetHeight();
    powerUp.deactivate();
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    if (state == MENU) {
        renderMenu();
    } else if (state == PLAYING || state == PAUSED) {
        // Línea central
        sf::RectangleShape centerLine(sf::Vector2f(5.f, 600.f));
        centerLine.setPosition(397.5f, 0.f);
        centerLine.setFillColor(sf::Color(100, 100, 100));
        window.draw(centerLine);
        
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        ball.draw(window);
        powerUp.draw(window);
        window.draw(leftScoreText);
        window.draw(rightScoreText);
        
        if (state == PAUSED) {
            renderPause();
        }
    } else if (state == GAME_OVER) {
        renderGameOver();
    }
    
    window.display();
}

void Game::renderMenu() {
    // Fondo con efecto
    sf::RectangleShape topBar(sf::Vector2f(800.f, 5.f));
    topBar.setPosition(0.f, 180.f);
    topBar.setFillColor(sf::Color::Cyan);
    window.draw(topBar);
    
    // Decoración de paletas en el menú
    sf::RectangleShape leftDecor(sf::Vector2f(15.f, 80.f));
    leftDecor.setPosition(50.f, 260.f);
    leftDecor.setFillColor(sf::Color(100, 200, 255));
    window.draw(leftDecor);
    
    sf::RectangleShape rightDecor(sf::Vector2f(15.f, 80.f));
    rightDecor.setPosition(735.f, 260.f);
    rightDecor.setFillColor(sf::Color(100, 200, 255));
    window.draw(rightDecor);
    
    // Power-up decorativo verde
    sf::CircleShape greenPowerUp(12.f);
    greenPowerUp.setPosition(470.f, 290.f);
    greenPowerUp.setFillColor(sf::Color::Green);
    window.draw(greenPowerUp);
    
    // Power-up decorativo rojo
    sf::CircleShape redPowerUp(12.f);
    redPowerUp.setPosition(470.f, 330.f);
    redPowerUp.setFillColor(sf::Color::Red);
    window.draw(redPowerUp);
    
    // Línea decorativa dorada
    sf::RectangleShape goldLine(sf::Vector2f(600.f, 3.f));
    goldLine.setPosition(100.f, 390.f);
    goldLine.setFillColor(sf::Color(255, 215, 0));
    window.draw(goldLine);
    
    window.draw(menuTitle);
    window.draw(menuInstruction);
    window.draw(menuControls);
    window.draw(menuPowerUps);
    window.draw(menuGoal);
}

void Game::renderPause() {
    sf::RectangleShape overlay(sf::Vector2f(800.f, 600.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);
    window.draw(pauseText);
    
    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setCharacterSize(30);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setString("Presiona ESPACIO o ESC para continuar");
    resumeText.setPosition(150.f, 330.f);
    window.draw(resumeText);
}

void Game::renderGameOver() {
    window.draw(gameOverText);
    window.draw(winnerText);
}